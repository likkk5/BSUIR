import { BookDTO } from './book.dto';

export type ReservationDTO = {
  id: number;
  book: BookDTO;
  bookId: number;
  description: string;
  userId: number;
  expectedReturnDate: Date;
  returnedAt: Date;
}
