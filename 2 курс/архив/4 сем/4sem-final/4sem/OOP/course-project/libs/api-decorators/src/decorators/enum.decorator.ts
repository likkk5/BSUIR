import { applyDecorators } from '@nestjs/common';
import { ApiProperty, ApiPropertyOptional } from '@nestjs/swagger';
import { ApiPropertyOptions } from '@nestjs/swagger/dist/decorators/api-property.decorator';
import { IsEnum, IsOptional } from 'class-validator';

import { INVALID_ENUM_VALUE } from '../constants/error.constants';

import { Decorator } from './decorator.type';

type PropertyEnumParams<T> = {
  isOptional?: boolean;
  example?: T[keyof T];
};

export function ApiPropertyEnum<TValues extends any[] | Record<string, any>>(
  values: TValues,
  { isOptional, example }: PropertyEnumParams<TValues> = {},
): Decorator {
  const propertyOptions: ApiPropertyOptions = { type: 'enum', enum: values, example };
  return applyDecorators(
    ...(isOptional ? [IsOptional(), ApiPropertyOptional(propertyOptions)] : [ApiProperty(propertyOptions)]),
    IsEnum(values as any, { message: INVALID_ENUM_VALUE, context: values }),
  );
}
