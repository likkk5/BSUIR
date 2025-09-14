import { Injectable } from '@nestjs/common';

import { ReservationEntity, ReservationToCreate } from '@libs/entities';
import { RESERVATION_ERROR } from '@libs/constants';
import { EntityNotFoundError, ServiceError } from '@libs/exceptions';

import { BooksRepository, ReservationsRepository } from '../repositories';
import { RESERVATION_CONSTANT } from '../constants';

import { BooksService } from './books.service';

@Injectable()
export class ReservationsService {
  constructor(
    private readonly reservationsRepository: ReservationsRepository,
    private readonly booksService: BooksService,
    private readonly booksRepository: BooksRepository,
  ) {}

  findMany(options: { userId?: number } = {}): Promise<ReservationEntity[]> {
    return this.reservationsRepository.find({ where: options, relations: { book: true } });
  }

  async create(reservationToCreate: Omit<ReservationToCreate, 'expectedReturnDate'>): Promise<ReservationEntity> {
    await this.validate(reservationToCreate);

    const expectedReturnDate = new Date();
    expectedReturnDate.setDate(expectedReturnDate.getDate() + RESERVATION_CONSTANT.MAX_RESERVATION_DAYS);

    await this.booksRepository.update(reservationToCreate.bookId, { amount: () => 'amount - 1' });
    const reservationEntity = await this.reservationsRepository.createAndSave({
      ...reservationToCreate,
      expectedReturnDate,
    });
    return this.findByIdOrFail(reservationEntity.id, reservationEntity.userId);
  }

  async deleteOne(id: number, userId: number): Promise<void> {
    const reservation = await this.findByIdOrFail(id, userId);
    await this.booksRepository.update(reservation.bookId, { amount: () => 'amount + 1' });
    await this.reservationsRepository.update(id, { returnedAt: new Date() });
  }

  async findByIdOrFail(id: number, userId: number): Promise<ReservationEntity> {
    const reservation = await this.reservationsRepository.findOne({ where: { id, userId }, relations: { book: true } });

    if (!reservation) {
      throw new EntityNotFoundError(RESERVATION_ERROR.RESERVATION_NOT_FOUND);
    }
    return reservation;
  }

  private async validate(props: Partial<ReservationToCreate>): Promise<void> {
    if (props.bookId) {
      const book = await this.booksService.findByIdOrFail(props.bookId);

      if (book.amount < 1) {
        throw new ServiceError(RESERVATION_ERROR.BOOK_AMOUNT_LESS_THAN_ONE);
      }
    }
  }

  async getStatistics(): Promise<{ moneyInDeposit: number; moneyFromRent: number }> {
    const reservations = await this.findMany();

    return reservations.reduce(
      (total, reservation) => {
        if (!reservation.returnedAt) {
          total.moneyInDeposit += reservation.book.depositPrice;
        } else {
          total.moneyFromRent += reservation.book.rentPrice;
        }

        return total;
      },
      {
        moneyInDeposit: 0,
        moneyFromRent: 0,
      },
    );
  }
}
