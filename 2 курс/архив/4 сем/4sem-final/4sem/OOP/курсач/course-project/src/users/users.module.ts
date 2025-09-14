import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';

import { UserEntity } from '@libs/entities';

import * as Repositories from './repositories';
import * as Services from './services';
import * as Controllers from './controllers';

@Module({
  imports: [TypeOrmModule.forFeature([UserEntity])],
  controllers: Object.values(Controllers),
  providers: [...Object.values(Services), ...Object.values(Repositories)],
})
export class UsersModule {}
