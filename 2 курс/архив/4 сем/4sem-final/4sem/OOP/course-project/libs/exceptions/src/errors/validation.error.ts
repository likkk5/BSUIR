import { ERROR_TYPE } from '../constants';

import { AbstractError, ErrorOptions } from './abstract.error';

export type ValidationDetail = {
  target: string;
  message: string;
  details?: Record<string, any>;
  context?: any;
};

export type ValidationErrorDetails = ValidationDetail[];

export class ValidationError extends AbstractError {
  constructor(details: ValidationDetail, options?: { cause?: ErrorOptions['cause'] });
  constructor(details: ValidationErrorDetails, options?: { cause?: ErrorOptions['cause'] });
  constructor(details: ValidationDetail | ValidationErrorDetails, options?: { cause?: ErrorOptions['cause'] }) {
    super(ERROR_TYPE.VALIDATION_ERROR, '', {
      details: Array.isArray(details) ? details : [details],
      ...(options?.cause ? options?.cause : {}),
    });
  }
}
