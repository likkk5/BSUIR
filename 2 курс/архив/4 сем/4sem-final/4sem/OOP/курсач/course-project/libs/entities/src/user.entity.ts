import { Column, Entity, Index } from 'typeorm';

import { USER_ROLE } from '@libs/constants';

import { BaseEntity } from './base.entity';

@Entity({ name: 'user' })
export class UserEntity extends BaseEntity {
  @Column()
  name!: string;

  @Column()
  password!: string;

  @Column()
  email!: string;

  @Index()
  @Column()
  normalizedEmail!: string;

  @Column({
    type: 'enum',
    enum: USER_ROLE,
    default: USER_ROLE.USER,
  })
  role!: USER_ROLE;
}
