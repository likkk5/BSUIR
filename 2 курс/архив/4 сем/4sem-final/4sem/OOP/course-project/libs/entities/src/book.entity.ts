import { Column, Entity } from 'typeorm';

import { BaseEntity } from './base.entity';

@Entity({ name: 'book' })
export class BookEntity extends BaseEntity {
  @Column()
  title!: string;

  @Column()
  genre!: string;

  @Column()
  author!: string;

  @Column()
  description!: string;

  @Column({ type: 'int' })
  amount!: number;

  @Column({ type: 'int' })
  depositPrice!: number;

  @Column({ type: 'int' })
  rentPrice!: number;
}

export type BookToCreate = Omit<BookEntity, 'id' | 'createdAt' | 'updatedAt'>;
