import { Injectable } from '@nestjs/common';
import { FindOptionsWhere, ILike } from 'typeorm';

import { BookEntity, BookToCreate } from '@libs/entities';
import { BooksBaseRepository } from '@libs/repositories';

@Injectable()
export class BooksRepository extends BooksBaseRepository {
  findMany({ search }: { search?: string } = {}): Promise<BookEntity[]> {
    const findOptions: FindOptionsWhere<BookEntity> = {};
    if (search) {
      findOptions['title'] = ILike(search);
    }
    return this.findBy(findOptions);
  }

  createAndSave(entityToCreate: BookToCreate): Promise<BookEntity> {
    const entity = this.create(entityToCreate);
    return this.save(entity);
  }
}
