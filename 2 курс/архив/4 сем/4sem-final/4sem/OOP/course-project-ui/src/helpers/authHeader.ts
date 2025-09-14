import AuthService from '../services/auth.service';

export default function authHeader(): { Authorization?: string } {
  const user = AuthService.getCurrentUser();

  if (user) {
    return { Authorization: 'Bearer ' + user.accessToken };
  } else {
    return {};
  }
}
