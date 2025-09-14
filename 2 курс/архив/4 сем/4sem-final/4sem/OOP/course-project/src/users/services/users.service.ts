import { Injectable } from '@nestjs/common';

import { UserEntity } from '@libs/entities';
import { USER_ERROR } from '@libs/constants';
import { EntityNotFoundError } from '@libs/exceptions';

import { UsersRepository } from '../repositories';

@Injectable()
export class UsersService {
  constructor(private readonly usersRepository: UsersRepository) {}

  findMany(): Promise<UserEntity[]> {
    return this.usersRepository.find();
  }

  async deleteByIdOrFail(id: number): Promise<void> {
    const user = await this.usersRepository.findOneBy({ id });

    if (!user) {
      throw new EntityNotFoundError(USER_ERROR.USER_NOT_FOUND);
    }

    await this.usersRepository.delete(id);
  }

  async findByIdOrFail(id: number): Promise<UserEntity> {
    const user = await this.usersRepository.findOneBy({ id });

    if (!user) {
      throw new EntityNotFoundError(USER_ERROR.USER_NOT_FOUND);
    }

    return user;
  }
}
