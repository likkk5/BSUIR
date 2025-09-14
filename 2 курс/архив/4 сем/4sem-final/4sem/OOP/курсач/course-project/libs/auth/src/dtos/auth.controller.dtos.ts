import { Expose, plainToClass } from 'class-transformer';

import { ApiPropertyEmail, ApiPropertyString } from '@libs/api-decorators';
import { Tokens } from '@libs/auth';

class TokensDTO {
  @Expose()
  @ApiPropertyString()
  accessToken!: string;

  @Expose()
  @ApiPropertyString()
  refreshToken!: string;

  constructor(data: Tokens) {
    Object.assign(this, plainToClass(TokensDTO, data, { excludeExtraneousValues: true }));
  }
}

export class SignUpBodyDTO {
  @ApiPropertyString({ trim: true })
  name!: string;

  @ApiPropertyEmail()
  email!: string;

  @ApiPropertyString()
  password!: string;
}

export class SignUpResponseDTO extends TokensDTO {}

export class LoginBodyDTO {
  @ApiPropertyEmail()
  email!: string;

  @ApiPropertyString()
  password!: string;
}

export class LoginResponseDTO extends TokensDTO {}

export class RenewTokensBodyDTO {
  @ApiPropertyString()
  refreshToken!: string;
}
export class RenewTokensResponseDTO extends TokensDTO {}

export class LogoutBodyDTO {
  @ApiPropertyString()
  refreshToken!: string;
}
