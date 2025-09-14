import { Body, Controller, HttpCode, Post } from '@nestjs/common';
import { ApiTags } from '@nestjs/swagger';

import {
  LoginBodyDTO,
  LoginResponseDTO,
  LogoutBodyDTO,
  RenewTokensBodyDTO,
  RenewTokensResponseDTO,
  SignUpBodyDTO,
  SignUpResponseDTO,
} from '../dtos';
import { AuthService } from '../services';

@Controller('auth')
@ApiTags('auth')
export class AuthController {
  constructor(private readonly authService: AuthService) {}

  @Post('signup')
  @HttpCode(200)
  async signUp(@Body() { email, password, name }: SignUpBodyDTO): Promise<SignUpResponseDTO> {
    const tokens = await this.authService.signUp(email, password, name);
    return new SignUpResponseDTO(tokens);
  }

  @Post('login')
  @HttpCode(200)
  async login(@Body() { email, password }: LoginBodyDTO): Promise<LoginResponseDTO> {
    const tokens = await this.authService.login(email, password);
    return new LoginResponseDTO(tokens);
  }

  @Post('renew-tokens')
  @HttpCode(200)
  async renewTokens(@Body() { refreshToken }: RenewTokensBodyDTO): Promise<RenewTokensResponseDTO> {
    const tokens = await this.authService.renewTokens(refreshToken);
    return new RenewTokensResponseDTO(tokens);
  }

  @Post('logout')
  @HttpCode(200)
  async logout(@Body() { refreshToken }: LogoutBodyDTO): Promise<void> {
    await this.authService.logout(refreshToken);
  }
}
