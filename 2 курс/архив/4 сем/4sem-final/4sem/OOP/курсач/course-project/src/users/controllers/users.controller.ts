import { Controller, Get, Param, UseGuards } from '@nestjs/common';
import { ApiBearerAuth, ApiNoContentResponse, ApiOkResponse, ApiTags } from '@nestjs/swagger';

import { Admin, JwtAuthGuard, JwtPayload, User } from '@libs/auth';

import { UsersService } from '../services';
import { GetUserParamsDTO, GetUserResponseDTO, GetUsersListResponseDTO } from '../dtos';

@ApiTags('users')
@Controller('users')
export class UsersController {
  constructor(private readonly usersService: UsersService) {}

  @Get('me')
  @ApiBearerAuth()
  @UseGuards(JwtAuthGuard)
  @ApiOkResponse({ type: GetUserResponseDTO })
  async getSelf(@User() { userId }: JwtPayload): Promise<GetUserResponseDTO> {
    const user = await this.usersService.findByIdOrFail(userId);
    return new GetUserResponseDTO(user);
  }

  @Get('me')
  @ApiBearerAuth()
  @UseGuards(JwtAuthGuard)
  @ApiNoContentResponse()
  async deleteSelf(@User() { userId }: JwtPayload): Promise<GetUserResponseDTO> {
    const user = await this.usersService.findByIdOrFail(userId);
    return new GetUserResponseDTO(user);
  }

  @Get(':id')
  @ApiBearerAuth()
  @UseGuards(JwtAuthGuard)
  @Admin()
  @ApiOkResponse({ type: GetUserResponseDTO })
  async getUser(@Param() { id }: GetUserParamsDTO): Promise<GetUserResponseDTO> {
    const user = await this.usersService.findByIdOrFail(id);
    return new GetUserResponseDTO(user);
  }

  @Get()
  @ApiBearerAuth()
  @UseGuards(JwtAuthGuard)
  @Admin()
  @ApiOkResponse({ type: GetUsersListResponseDTO })
  async getUsersList(): Promise<GetUsersListResponseDTO> {
    const users = await this.usersService.findMany();
    return new GetUsersListResponseDTO(users);
  }
}
