import { DataSource, Repository } from 'typeorm';
import { Injectable } from '@nestjs/common';

import { RefreshTokenEntity } from '@libs/entities';

@Injectable()
export class RefreshTokensBaseRepository extends Repository<RefreshTokenEntity> {
  constructor(protected readonly dataSource: DataSource) {
    super(RefreshTokenEntity, dataSource.createEntityManager());
  }
}
