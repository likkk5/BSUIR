import { DynamicModule, Module } from '@nestjs/common';
import { APP_FILTER, APP_PIPE } from '@nestjs/core/constants';

import { HttpExceptionFilter } from './filters/';
import { ClassValidationPipe } from './middlewares';

@Module({})
export class ExceptionsModule {
  static forRoot({
    includeValidationPipe = true,
  }: {
    includeValidationPipe?: boolean;
  } = {}): DynamicModule {
    const providers: any[] = [
      {
        provide: APP_FILTER,
        useClass: HttpExceptionFilter,
      },
    ];

    if (includeValidationPipe) {
      providers.push({
        provide: APP_PIPE,
        useClass: ClassValidationPipe,
      });
    }

    return {
      module: ExceptionsModule,
      providers,
    };
  }
}
