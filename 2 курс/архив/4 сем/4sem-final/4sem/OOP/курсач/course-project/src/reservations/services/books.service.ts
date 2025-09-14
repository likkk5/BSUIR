import { Injectable } from '@nestjs/common';

import { BookEntity } from '@libs/entities';
import { BOOK_ERROR } from '@libs/constants';
import { EntityNotFoundError } from '@libs/exceptions';

import { BooksRepository } from '../repositories';

@Injectable()
export class BooksService {
  constructor(private readonly booksRepository: BooksRepository) {}

  async findByIdOrFail(id: number): Promise<BookEntity> {
    const book = await this.booksRepository.findOneBy({ id });

    if (!book) {
      throw new EntityNotFoundError(BOOK_ERROR.BOOK_NOT_FOUND);
    }

    return book;
  }
}
