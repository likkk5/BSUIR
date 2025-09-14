import { USER_ROLE } from '../constants';

export type UserDTO = {
  id: number;
  name: string;
  email: string;
  role: USER_ROLE;
};
