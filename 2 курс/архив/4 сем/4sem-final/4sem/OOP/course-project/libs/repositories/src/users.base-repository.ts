import { DataSource, Repository } from 'typeorm';
import { Injectable } from '@nestjs/common';

import { UserEntity } from '@libs/entities';

@Injectable()
export class UsersBaseRepository extends Repository<UserEntity> {
  constructor(protected readonly dataSource: DataSource) {
    super(UserEntity, dataSource.createEntityManager());
  }
}
