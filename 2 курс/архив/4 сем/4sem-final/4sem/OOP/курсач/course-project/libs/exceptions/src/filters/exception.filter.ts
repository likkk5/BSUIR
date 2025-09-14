import { ArgumentsHost, Catch, ExceptionFilter, HttpStatus, Logger } from '@nestjs/common';
import { Response } from 'express';

import { AbstractError } from '@libs/exceptions';

import { getErrorStatus } from '../helpers';

@Catch()
export class HttpExceptionFilter implements ExceptionFilter {
  private readonly logger = new Logger(HttpExceptionFilter.name);

  catch(exception: Error & { details?: AbstractError['details'] }, host: ArgumentsHost): void {
    const ctx = host.switchToHttp();
    const response: Response = ctx.getResponse();

    const status = getErrorStatus(exception);
    if (status < HttpStatus.INTERNAL_SERVER_ERROR) {
      response.status(status).json({
        status,
        name: exception.name,
        message: exception.message,
        details: exception.details || [],
      });
      return;
    }

    this.logger.error(exception, exception.stack);

    response.status(HttpStatus.INTERNAL_SERVER_ERROR).json({
      status: HttpStatus.INTERNAL_SERVER_ERROR,
      message: 'Internal Server Error',
    });
  }
}
