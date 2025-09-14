import { applyDecorators } from '@nestjs/common';
import { ApiProperty, ApiPropertyOptional } from '@nestjs/swagger';
import { ApiPropertyOptions } from '@nestjs/swagger/dist/decorators/api-property.decorator';
import { Type } from 'class-transformer';
import { IsDate, IsOptional, MinDate } from 'class-validator';

import { INVALID_DATE, INVALID_LIMIT_VALUE } from '../constants/error.constants';

export function ApiPropertyDate({
  isOptional,
  minDate,
  example,
}: { isOptional?: boolean; minDate?: Date; example?: string } = {}) {
  const propertyOptions: ApiPropertyOptions = { type: Date, example: example || '2022-01-11T17:28:44.079Z' };

  return applyDecorators(
    ...(isOptional ? [IsOptional(), ApiPropertyOptional(propertyOptions)] : [ApiProperty(propertyOptions)]),
    IsDate({ message: INVALID_DATE }),
    ...(minDate ? [MinDate(minDate, { message: INVALID_LIMIT_VALUE, context: { minValue: minDate } })] : []),
    Type(() => Date),
  );
}
