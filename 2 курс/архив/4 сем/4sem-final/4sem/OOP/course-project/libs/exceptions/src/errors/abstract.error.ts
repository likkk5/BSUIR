import { ERROR_TYPE } from '../constants';

export type ErrorOptions = {
  cause?: { [key: string]: any };
  details?: { [key: string]: any }[];
};

export class AbstractError extends Error {
  readonly name: ERROR_TYPE;
  readonly message: string;
  readonly details: { [key: string]: any }[] = [];
  readonly cause: { [key: string]: any } | null = null;

  constructor(name: ERROR_TYPE, message: string, options?: ErrorOptions) {
    super();
    this.name = name;
    this.message = message;
    this.details = options?.details || [];
    this.cause = options?.cause || null;
  }

  public toString(): string {
    return `${this.name}: ${this.message}. Details: ${JSON.stringify(this.details)}`;
  }
}
