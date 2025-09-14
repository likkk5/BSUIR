import { Injectable } from '@nestjs/common';
import validator from 'validator';

import { ValidationError } from '@libs/exceptions';
import { AUTH_ERROR } from '@libs/constants';

@Injectable()
export class UserEmailService {
  normalizeEmail(email: string): string {
    const normalizedEmail = validator.normalizeEmail(email, {});

    if (!normalizedEmail) {
      throw new ValidationError({ target: 'email', message: AUTH_ERROR.INVALID_EMAIL });
    }

    return normalizedEmail;
  }
}
