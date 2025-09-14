import { applyDecorators } from '@nestjs/common';
import { ApiProperty, ApiPropertyOptional } from '@nestjs/swagger';
import { ApiPropertyOptions } from '@nestjs/swagger/dist/decorators/api-property.decorator';
import { Type } from 'class-transformer';
import { IsInt, IsOptional, Max, Min } from 'class-validator';

import { FIELD_MUST_BE_AN_INTEGER, INVALID_LIMIT_VALUE } from '../constants/error.constants';

class ApiPropertyNumberParams {
  isOptional?: boolean;
  min?: number;
  max?: number;
  each?: boolean;
  example?: number;
}

export function ApiPropertyNumber({ isOptional, min, max, each, example }: ApiPropertyNumberParams = { example: 1 }) {
  const propertyOptions: ApiPropertyOptions = {
    type: Number,
    example: each ? [1, 2, 3] : example,
    isArray: each,
    ...(min ? [{ minimum: min }] : []),
    ...(max ? [{ maximum: max }] : []),
  };

  return applyDecorators(
    ...(isOptional ? [IsOptional(), ApiPropertyOptional(propertyOptions)] : [ApiProperty(propertyOptions)]),
    IsInt({ message: FIELD_MUST_BE_AN_INTEGER, each }),
    Type(() => Number),
    ...(!isNaN(min!) ? [Min(min!, { message: INVALID_LIMIT_VALUE, context: { minValue: min }, each })] : []),
    ...(!isNaN(max!) ? [Max(max!, { message: INVALID_LIMIT_VALUE, context: { maxValue: max }, each })] : []),
  );
}
