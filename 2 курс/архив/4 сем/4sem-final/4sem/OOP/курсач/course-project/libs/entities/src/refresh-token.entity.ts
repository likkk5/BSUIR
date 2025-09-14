import { Column, Entity, ManyToOne } from 'typeorm';

import { UserEntity } from './user.entity';
import { BaseEntity } from './base.entity';

@Entity({ name: 'refreshToken' })
export class RefreshTokenEntity extends BaseEntity {
  @ManyToOne(() => UserEntity, {
    onDelete: 'CASCADE',
  })
  user!: UserEntity;

  @Column()
  userId!: number;

  @Column({ default: true })
  isActive!: boolean;
}
