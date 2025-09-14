import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';

import { ExceptionsModule } from '@libs/exceptions';
import { AuthModule } from '@libs/auth';
import { typeormOptions } from 'ormconfig';

import { BooksModule } from './books/books.module';
import { UsersModule } from './users/users.module';
import { ReservationsModule } from './reservations/reservations.module';

@Module({
  imports: [
    ExceptionsModule.forRoot(),
    TypeOrmModule.forRoot(typeormOptions),
    AuthModule,
    UsersModule,
    BooksModule,
    ReservationsModule,
  ],
  controllers: [],
  providers: [],
})
export class AppModule {}
