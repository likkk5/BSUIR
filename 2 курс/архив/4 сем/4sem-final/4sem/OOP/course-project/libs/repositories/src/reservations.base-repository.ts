import { DataSource, Repository } from 'typeorm';
import { Injectable } from '@nestjs/common';

import { ReservationEntity } from '@libs/entities';

@Injectable()
export class ReservationsBaseRepository extends Repository<ReservationEntity> {
  constructor(protected readonly dataSource: DataSource) {
    super(ReservationEntity, dataSource.createEntityManager());
  }
}
