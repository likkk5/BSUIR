export enum API {
  URL = 'http://localhost:3001',
}

export const BASE_URL = `${API.URL}/api/v1`;

export const AUTH_URL = {
  LOGIN: BASE_URL + '/auth/login',
  SIGNUP: BASE_URL + '/auth/signup',
} as const;

export const USER_URL = {
  GET_SELF: BASE_URL + '/users/me',
} as const;

export const BOOK_URL = {
  BOOK_BY_ID: (id: number) => `${BASE_URL}/books/${id}`,
  BOOKS: `${BASE_URL}/books`,
} as const;

export const RESERVATION_URL = {
  RESERVATION_BY_ID: (id: number) => `${BASE_URL}/reservations/${id}`,
  RESERVATIONS: `${BASE_URL}/reservations`,
  STATISTICS: `${BASE_URL}/reservations/statistics`,
};
