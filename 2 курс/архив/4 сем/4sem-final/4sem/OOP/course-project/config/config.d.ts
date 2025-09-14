declare module 'config' {
  export const CORS: boolean;

  export const POSTGRES: {
    readonly HOST: string;
    readonly USERNAME: string;
    readonly PASSWORD: string;
    readonly PORT: number;
    readonly DB: string;
    readonly RETRY_ATTEMPTS: number;
    readonly RETRY_DELAY: number;
  };

  export const API: {
    readonly PORT: number;
  };

  export const JWT: {
    readonly ACCESS_SECRET: string;
    readonly ACCESS_EXPIRATION_TIME: string;
    readonly REFRESH_EXPIRATION_TIME: string;
  };
}
