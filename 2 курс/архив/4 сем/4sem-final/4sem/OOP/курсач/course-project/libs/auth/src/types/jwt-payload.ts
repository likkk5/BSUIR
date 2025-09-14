import { USER_ROLE } from '@libs/constants';

export class JwtPayload {
  userId!: number;
  userRole!: USER_ROLE;
}
