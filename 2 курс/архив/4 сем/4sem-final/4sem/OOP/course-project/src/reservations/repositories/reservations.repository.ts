import { Injectable } from '@nestjs/common';

import { ReservationEntity, ReservationToCreate } from '@libs/entities';
import { ReservationsBaseRepository } from '@libs/repositories';

@Injectable()
export class ReservationsRepository extends ReservationsBaseRepository {
  createAndSave(entityToCreate: ReservationToCreate): Promise<ReservationEntity> {
    const entity = this.create(entityToCreate);
    return this.save(entity);
  }
}
