import { Injectable } from '@nestjs/common';
import { JwtService } from '@nestjs/jwt';
import * as config from 'config';

import { Tokens } from '@libs/auth';
import { ServiceError } from '@libs/exceptions';
import { USER_ROLE, AUTH_ERROR } from '@libs/constants';
import { RefreshTokenEntity } from '@libs/entities';

import { RefreshTokensRepository } from '../repositories';

import { UsersService } from './users.service';

type TokenAssertion = (refreshToken: RefreshTokenEntity) => asserts refreshToken is RefreshTokenEntity;

@Injectable()
export class TokensService {
  constructor(
    private readonly jwtService: JwtService,
    private readonly usersService: UsersService,
    private readonly refreshTokensRepository: RefreshTokensRepository,
  ) {}

  async renewTokens(refreshToken: string): Promise<Tokens> {
    const tokenId = this.extractTokenId(refreshToken);

    const token = await this.findTokenByIdOrFail(tokenId);

    const [user] = await Promise.all([this.usersService.findByIdOrFail(token.userId), this.deactivateToken(tokenId)]);

    return this.generateNewPairOfTokens(user);
  }

  extractTokenId(refreshToken: string): number {
    const { id: tokenId } = this.jwtService.verify<{ id: number }>(refreshToken);
    return tokenId;
  }

  async generateNewPairOfTokens({ id: userId, role }: { id: number; role: USER_ROLE }): Promise<Tokens> {
    const accessToken = this.generateAccessToken(userId, role);
    const refreshToken = await this.generateRefreshToken(userId);

    return { accessToken, refreshToken };
  }

  async deactivateToken(tokenId: number): Promise<void> {
    await this.refreshTokensRepository.updateTokenById(tokenId, { isActive: false });
  }

  private generateAccessToken(userId: number, userRole: USER_ROLE): string {
    const payload = { userId, userRole };
    return this.jwtService.sign(payload);
  }

  private async generateRefreshToken(userId: number): Promise<string> {
    const token = await this.refreshTokensRepository.createAndSave(userId);
    const payload = { id: token.id };

    return this.jwtService.sign(payload, { expiresIn: config.JWT.REFRESH_EXPIRATION_TIME });
  }

  private async findTokenByIdOrFail(id: number): Promise<RefreshTokenEntity> {
    const token = await this.refreshTokensRepository.findOneBy({ id });

    await this.verifyRefreshToken(token);

    return token as RefreshTokenEntity;
  }

  private async verifyRefreshToken(refreshToken: RefreshTokenEntity | null): Promise<void> {
    if (!refreshToken) {
      throw new ServiceError(AUTH_ERROR.INCORRECT_REFRESH_TOKEN);
    }

    if (!refreshToken.isActive) {
      await this.deactivateAllTokensByUser(refreshToken.userId);
      throw new ServiceError(AUTH_ERROR.INCORRECT_REFRESH_TOKEN);
    }
  }

  private async deactivateAllTokensByUser(userId: number): Promise<void> {
    await this.refreshTokensRepository.updateTokensByUserId(userId, { isActive: false });
  }
}
