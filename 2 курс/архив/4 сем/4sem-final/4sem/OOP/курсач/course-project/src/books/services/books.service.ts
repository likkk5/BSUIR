import { Injectable } from '@nestjs/common';

import { BookEntity, BookToCreate } from '@libs/entities';
import { BOOK_ERROR } from '@libs/constants';
import { EntityNotFoundError } from '@libs/exceptions';

import { BooksRepository } from '../repositories';

@Injectable()
export class BooksService {
  constructor(private readonly booksRepository: BooksRepository) {}

  findMany(options: { search?: string } = {}): Promise<BookEntity[]> {
    return this.booksRepository.findMany(options);
  }

  create(bookToCreate: BookToCreate): Promise<BookEntity> {
    return this.booksRepository.createAndSave(bookToCreate);
  }

  async updateOne(id: number, bookProps: Partial<BookToCreate>): Promise<BookEntity> {
    await this.booksRepository.update(id, bookProps);
    return this.findByIdOrFail(id);
  }

  async deleteOne(id: number): Promise<void> {
    await this.findByIdOrFail(id);
    await this.booksRepository.delete(id);
  }

  async findByIdOrFail(id: number): Promise<BookEntity> {
    const book = await this.booksRepository.findOneBy({ id });

    if (!book) {
      throw new EntityNotFoundError(BOOK_ERROR.BOOK_NOT_FOUND);
    }

    return book;
  }
}
