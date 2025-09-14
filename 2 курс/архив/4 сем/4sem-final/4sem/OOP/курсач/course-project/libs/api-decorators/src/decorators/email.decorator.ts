import { applyDecorators } from '@nestjs/common';
import { ApiProperty, ApiPropertyOptional } from '@nestjs/swagger';
import { ApiPropertyOptions } from '@nestjs/swagger/dist/decorators/api-property.decorator';
import { IsEmail, IsOptional, MaxLength } from 'class-validator';

import { INVALID_EMAIL, TOO_LONG_STRING } from '../constants/error.constants';

import { Decorator } from './decorator.type';

export function ApiPropertyEmail({ isOptional }: { isOptional?: boolean } = {}): Decorator {
  const propertyOptions: ApiPropertyOptions = { type: String, example: 'koko@ko.ko', description: 'Email' };

  return applyDecorators(
    ...(isOptional ? [IsOptional(), ApiPropertyOptional(propertyOptions)] : [ApiProperty(propertyOptions)]),
    IsEmail({}, { message: INVALID_EMAIL }),
    MaxLength(256, { message: TOO_LONG_STRING }),
  );
}
