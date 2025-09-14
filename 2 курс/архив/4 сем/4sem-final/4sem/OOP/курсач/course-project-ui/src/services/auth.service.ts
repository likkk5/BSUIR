import axios from 'axios';

import { TokensDto, UserDTO } from '../types';
import { AUTH_KEY, AUTH_URL } from '../constants';

export default class AuthService {
  static async signup(payload: Omit<UserDTO, 'id' | 'role'> & { password: string }): Promise<void> {
    const { data } = await axios.post<TokensDto>(AUTH_URL.SIGNUP, payload);

    if (data.accessToken) {
      localStorage.setItem(AUTH_KEY, JSON.stringify(data));
    }
  }

  static async login(payload: { email: string; password: string }): Promise<void> {
    const { data } = await axios.post<TokensDto>(AUTH_URL.LOGIN, payload);

    if (data.accessToken) {
      localStorage.setItem(AUTH_KEY, JSON.stringify(data));
    }
  }

  static logout(): void {
    localStorage.removeItem(AUTH_KEY);
  }

  static getCurrentUser(): TokensDto | null {
    const user = localStorage.getItem(AUTH_KEY);

    if (!user) {
      return null;
    }

    return JSON.parse(user);
  }
}
