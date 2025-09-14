import { DataSource, Repository } from 'typeorm';
import { Injectable } from '@nestjs/common';

import { BookEntity } from '@libs/entities';

@Injectable()
export class BooksBaseRepository extends Repository<BookEntity> {
  constructor(protected readonly dataSource: DataSource) {
    super(BookEntity, dataSource.createEntityManager());
  }
}
