import { BookDTO, Paginated } from '../types';
import axios from '../helpers/axios';
import { BOOK_URL } from '../constants';

export default class BooksService {
  static async getBook(id: number): Promise<BookDTO> {
    const { data } = await axios.get<BookDTO>(BOOK_URL.BOOK_BY_ID(id));
    return data;
  }

  static async getBooksList(): Promise<Paginated<BookDTO>> {
    const { data } = await axios.get<Paginated<BookDTO>>(BOOK_URL.BOOKS);
    return data;
  }

  static async createBook(bookToCreate: Omit<BookDTO, 'id'>): Promise<BookDTO> {
    const { data } = await axios.post<BookDTO>(BOOK_URL.BOOKS, bookToCreate);
    return data;
  }

  static async updateBook(
    id: number, bookProps: Partial<BookDTO>,
  ): Promise<BookDTO> {
    const { data } = await axios.patch<BookDTO>(BOOK_URL.BOOK_BY_ID(id), bookProps);
    return data;
  }

  static async deleteBook(id: number): Promise<void> {
    await axios.delete(BOOK_URL.BOOK_BY_ID(id));
  }
}
