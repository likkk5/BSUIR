import { ApiPropertyNumber } from './number.decorator';
export const MAX_DB_INTEGER = 2147483648;

export function ApiPropertyId({ isOptional, each }: { isOptional?: boolean; each?: boolean } = {}) {
  return ApiPropertyNumber({ isOptional, min: 1, max: MAX_DB_INTEGER, each });
}
