import { Injectable } from '@nestjs/common';

import { UserEntity } from '@libs/entities';
import { EntityNotFoundError, ServiceError } from '@libs/exceptions';
import { AUTH_ERROR } from '@libs/constants';

import { UsersRepository } from '../repositories';

import { UserEmailService } from './user-email.service';

@Injectable()
export class UsersService {
  constructor(private readonly usersRepository: UsersRepository, private readonly userEmailService: UserEmailService) {}
  createAndSave(email: string, password: string, name: string): Promise<UserEntity> {
    const normalizedEmail = this.userEmailService.normalizeEmail(email);
    return this.usersRepository.createAndSave(email, normalizedEmail, password, name);
  }

  async checkIsEmailUniqueOrFail(email: string): Promise<void> | never {
    const user = await this.normalizeEmailAndFind(email);
    if (user) {
      throw new ServiceError(AUTH_ERROR.EMAIL_ALREADY_EXISTS);
    }
  }

  normalizeEmailAndFind(email: string): Promise<UserEntity | null> {
    const normalizedEmail = this.userEmailService.normalizeEmail(email);
    return this.usersRepository.findOneBy({ normalizedEmail });
  }

  async normalizeEmailAndFindOrFail(email: string): Promise<UserEntity> {
    const user = await this.normalizeEmailAndFind(email);

    if (!user) {
      throw new EntityNotFoundError(AUTH_ERROR.USER_NOT_FOUND);
    }

    return user;
  }

  async findByIdOrFail(id: number): Promise<UserEntity> {
    const user = await this.usersRepository.findOneBy({ id });

    if (!user) {
      throw new EntityNotFoundError(AUTH_ERROR.USER_NOT_FOUND);
    }

    return user;
  }
}
