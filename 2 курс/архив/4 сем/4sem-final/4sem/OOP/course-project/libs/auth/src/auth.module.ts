import { Module } from '@nestjs/common';
import { JwtModule } from '@nestjs/jwt';
import * as config from 'config';
import { JWT } from 'config';
import { TypeOrmModule } from '@nestjs/typeorm';

import { RefreshTokenEntity, UserEntity } from '@libs/entities';

import * as Services from './services';
import { AuthController } from './controllers';
import { JwtAuthStrategy } from './strategies';
import * as Repositories from './repositories';

@Module({
  imports: [
    TypeOrmModule.forFeature([UserEntity, RefreshTokenEntity]),
    JwtModule.register({
      secret: JWT.ACCESS_SECRET,
      signOptions: { expiresIn: config.JWT.ACCESS_EXPIRATION_TIME },
    }),
  ],
  providers: [...Object.values(Services), JwtAuthStrategy, ...Object.values(Repositories)],
  controllers: [AuthController],
})
export class AuthModule {}
