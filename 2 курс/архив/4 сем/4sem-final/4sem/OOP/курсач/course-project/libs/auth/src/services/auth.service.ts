import { Injectable } from '@nestjs/common';
import bcrypt from 'bcryptjs';
import { JwtService } from '@nestjs/jwt';

import { HASH, Tokens } from '@libs/auth';

import { TokensService } from './tokens.service';
import { UsersService } from './users.service';
import { AuthPasswordService } from './auth-password.service';

@Injectable()
export class AuthService {
  constructor(
    private readonly usersService: UsersService,
    private readonly authPasswordService: AuthPasswordService,
    private readonly jwtService: JwtService,
    private readonly tokensService: TokensService,
  ) {}

  async signUp(email: string, password: string, name: string): Promise<Tokens> {
    this.authPasswordService.validatePassword(password);
    await this.usersService.checkIsEmailUniqueOrFail(email);

    const hashedPassword = await bcrypt.hash(password, HASH.SALT_LENGTH);
    const user = await this.usersService.createAndSave(email, hashedPassword, name);

    return this.tokensService.generateNewPairOfTokens(user);
  }

  async login(email: string, password: string): Promise<Tokens> {
    const user = await this.usersService.normalizeEmailAndFindOrFail(email);

    await this.authPasswordService.checkIsPasswordCorrectOrFail(user, password);

    return this.tokensService.generateNewPairOfTokens(user);
  }

  renewTokens(refreshToken: string): Promise<Tokens> {
    return this.tokensService.renewTokens(refreshToken);
  }

  logout(refreshToken: string): Promise<void> {
    const tokenId = this.tokensService.extractTokenId(refreshToken);
    return this.tokensService.deactivateToken(tokenId);
  }
}
