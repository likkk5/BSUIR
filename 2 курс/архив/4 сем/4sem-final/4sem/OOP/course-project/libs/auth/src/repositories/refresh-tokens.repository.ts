import { Injectable } from '@nestjs/common';

import { RefreshTokensBaseRepository } from '@libs/repositories';
import { RefreshTokenEntity } from '@libs/entities';

@Injectable()
export class RefreshTokensRepository extends RefreshTokensBaseRepository {
  createAndSave(userId: number): Promise<RefreshTokenEntity> {
    const token = this.create({ userId });
    return this.save(token);
  }

  async updateTokenById(id: number, tokenProps: Partial<RefreshTokenEntity>): Promise<void> {
    await this.update(id, tokenProps);
  }

  async updateTokensByUserId(userId: number, tokenProps: Partial<RefreshTokenEntity>): Promise<void> {
    await this.update({ userId }, tokenProps);
  }
}
