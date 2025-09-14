import { HttpException, HttpStatus } from '@nestjs/common';

import { EntityNotFoundError, ServiceError, ValidationError } from '@libs/exceptions';

export const getErrorStatus = (exception: Error): number => {
  if (exception instanceof HttpException) {
    return exception.getStatus();
  }
  if (exception instanceof EntityNotFoundError) {
    return HttpStatus.NOT_FOUND;
  }
  if (exception instanceof ServiceError) {
    return HttpStatus.BAD_REQUEST;
  }
  if (exception instanceof ValidationError) {
    return HttpStatus.UNPROCESSABLE_ENTITY;
  }
  return HttpStatus.INTERNAL_SERVER_ERROR;
};
