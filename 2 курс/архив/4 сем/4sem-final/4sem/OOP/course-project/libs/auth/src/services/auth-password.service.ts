import { Injectable } from '@nestjs/common';
import bcrypt from 'bcryptjs';
import validator from 'validator';

import { AUTH_ERROR } from '@libs/constants';
import { UserEntity } from '@libs/entities';
import { ServiceError, ValidationError } from '@libs/exceptions';
import { PASSWORD_VALIDATION_CONSTANTS } from '@libs/auth';

@Injectable()
export class AuthPasswordService {
  async checkIsPasswordCorrectOrFail(user: UserEntity, password: string): Promise<void> | never {
    const isPasswordCorrect = await bcrypt.compare(password, user.password);
    if (!isPasswordCorrect) {
      throw new ServiceError(AUTH_ERROR.INCORRECT_PASSWORD);
    }
  }

  validatePassword(password: string): void | never {
    const isPassportStrong = validator.isStrongPassword(password, {
      minLength: PASSWORD_VALIDATION_CONSTANTS.MIN_LENGTH,
      minLowercase: PASSWORD_VALIDATION_CONSTANTS.MIN_LOWERCASE_CHARACTERS,
      minUppercase: PASSWORD_VALIDATION_CONSTANTS.MIN_UPPERCASE_CHARACTERS,
      minNumbers: PASSWORD_VALIDATION_CONSTANTS.MIN_NUMBERS,
      minSymbols: PASSWORD_VALIDATION_CONSTANTS.MIN_SYMBOLS,
    });

    if (!isPassportStrong) {
      throw new ValidationError({ target: 'password', message: AUTH_ERROR.INCORRECT_PASSWORD });
    }
  }
}
