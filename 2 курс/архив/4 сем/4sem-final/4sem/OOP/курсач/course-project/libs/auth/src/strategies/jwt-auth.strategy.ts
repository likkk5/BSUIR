import { ExtractJwt, Strategy } from 'passport-jwt';
import { PassportStrategy } from '@nestjs/passport';
import { Injectable } from '@nestjs/common';
import { JWT } from 'config';

import { COOKIE } from '@libs/auth';

import { JwtPayload } from '../types';

@Injectable()
export class JwtAuthStrategy extends PassportStrategy(Strategy) {
  constructor() {
    super({
      jwtFromRequest: ExtractJwt.fromExtractors([
        JwtAuthStrategy.extractJWTFromCookies,
        ExtractJwt.fromAuthHeaderAsBearerToken(),
      ]),
      ignoreExpiration: false,
      secretOrKey: JWT.ACCESS_SECRET,
    });
  }

  validate(payload: JwtPayload): JwtPayload {
    return { userId: payload.userId, userRole: payload.userRole };
  }

  private static extractJWTFromCookies(req): string | null {
    if (req) {
      if (req.cookies && req.cookies[COOKIE.ACCESS_TOKEN]) {
        return req.cookies[COOKIE.ACCESS_TOKEN];
      }
    }
    return null;
  }
}
