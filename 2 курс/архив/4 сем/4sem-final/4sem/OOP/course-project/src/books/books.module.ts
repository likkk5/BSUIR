import { Module } from '@nestjs/common';

import * as Repositories from './repositories';
import * as Services from './services';
import * as Controllers from './controllers';

@Module({
  controllers: Object.values(Controllers),
  providers: [...Object.values(Services), ...Object.values(Repositories)],
})
export class BooksModule {}
