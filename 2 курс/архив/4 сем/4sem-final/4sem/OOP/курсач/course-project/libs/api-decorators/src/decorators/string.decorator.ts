import { applyDecorators } from '@nestjs/common';
import { ApiProperty, ApiPropertyOptional } from '@nestjs/swagger';
import { ApiPropertyOptions } from '@nestjs/swagger/dist/decorators/api-property.decorator';
import { isDefined, IsOptional, IsString, Matches, MaxLength, MinLength } from 'class-validator';
import { Transform } from 'class-transformer';

import { NOT_MATCHES_TO_PATTERN, TOO_LONG_STRING, TOO_SHORT_STRING } from '../constants/error.constants';

import { Decorator } from './decorator.type';

type PropertyStringParams = {
  isOptional?: boolean;
  minLength?: number;
  maxLength?: number;
  example?: string;
  pattern?: RegExp;
  trim?: boolean;
  toLower?: boolean;
};

export function ApiPropertyString({
  isOptional,
  minLength,
  maxLength,
  example,
  pattern,
  trim,
  toLower,
}: PropertyStringParams = {}): Decorator {
  const propertyOptions: ApiPropertyOptions = {
    type: String,
    example,
    ...(pattern && { pattern: pattern.toString() }),
    ...(minLength && { minLength }),
    ...(maxLength && { maxLength }),
  };

  return applyDecorators(
    ...(isOptional ? [IsOptional(), ApiPropertyOptional(propertyOptions)] : [ApiProperty(propertyOptions)]),
    ...(trim ? [IsString(), Transform(({ value }) => value.trim())] : [IsString()]),
    ...(!isNaN(minLength!) ? [MinLength(minLength!, { message: TOO_SHORT_STRING, context: { minLength } })] : []),
    ...(!isNaN(maxLength!) ? [MaxLength(maxLength!, { message: TOO_LONG_STRING, context: { maxLength } })] : []),
    ...(isDefined(pattern)
      ? [Matches(pattern!, { message: NOT_MATCHES_TO_PATTERN, context: { pattern: pattern!.toString() } })]
      : []),
    ...(toLower ? [Transform(({ value }) => value.toLowerCase())] : []),
  );
}
