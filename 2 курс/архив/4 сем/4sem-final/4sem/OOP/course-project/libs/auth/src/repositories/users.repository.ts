import { Injectable } from '@nestjs/common';

import { UserEntity } from '@libs/entities';
import { UsersBaseRepository } from '@libs/repositories';

@Injectable()
export class UsersRepository extends UsersBaseRepository {
  createAndSave(email: string, normalizedEmail: string, password: string, name: string): Promise<UserEntity> {
    const user = this.create({
      email,
      normalizedEmail,
      name,
      password,
    });

    return this.save(user);
  }
}
