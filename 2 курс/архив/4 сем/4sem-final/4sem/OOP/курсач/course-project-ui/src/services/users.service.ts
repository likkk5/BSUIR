import { UserDTO } from '../types';
import axios from '../helpers/axios';
import { USER_URL } from '../constants';
import AuthService from './auth.service';

export default class UsersService {

  static async getSelf(): Promise<UserDTO | null> {
    if (!AuthService.getCurrentUser()) {
      return null;
    }

    try {
      const { data } = await axios.get<UserDTO>(USER_URL.GET_SELF);
      return data;
    } catch (err) {
      return null;
    }
  }
}
