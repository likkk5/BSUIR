import { Column, Entity, ManyToOne } from 'typeorm';

import { BaseEntity } from './base.entity';
import { BookEntity } from './book.entity';
import { UserEntity } from './user.entity';

@Entity({ name: 'reservation' })
export class ReservationEntity extends BaseEntity {
  @ManyToOne(() => BookEntity, {
    onDelete: 'CASCADE',
  })
  book!: BookEntity;

  @Column()
  bookId!: number;

  @ManyToOne(() => UserEntity, {
    onDelete: 'CASCADE',
  })
  user!: UserEntity;

  @Column()
  userId!: number;

  @Column({ type: 'timestamptz' })
  expectedReturnDate!: Date;

  @Column({ type: 'timestamptz', nullable: true })
  returnedAt!: Date;
}

export type ReservationToCreate = Pick<ReservationEntity, 'bookId' | 'userId' | 'expectedReturnDate'>;
