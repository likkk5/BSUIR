import { Body, Controller, Delete, Get, Param, Post, UseGuards } from '@nestjs/common';
import { ApiBearerAuth, ApiCreatedResponse, ApiNoContentResponse, ApiOkResponse, ApiTags } from '@nestjs/swagger';

import { Admin, JwtAuthGuard, JwtPayload, User } from '@libs/auth';

import { ReservationsService } from '../services';
import {
  GetReservationParamsDTO,
  GetReservationResponseDTO,
  GetReservationsListResponseDTO,
  GetStatisticsResponseDTO,
  ReserveBookBodyDTO,
  ReserveBookResponseDTO,
  ReturnReservationParamsDTO,
} from '../dtos';

@ApiTags('reservations')
@Controller('reservations')
export class ReservationsController {
  @ApiBearerAuth()
  @UseGuards(JwtAuthGuard)
  @Admin()
  @Get('statistics')
  async getStatistics(): Promise<GetStatisticsResponseDTO> {
    const statistics = await this.reservationsService.getStatistics();
    return new GetStatisticsResponseDTO(statistics);
  }

  constructor(private readonly reservationsService: ReservationsService) {}

  @ApiBearerAuth()
  @UseGuards(JwtAuthGuard)
  @Get(':id')
  @ApiOkResponse({ type: GetReservationResponseDTO })
  async getReservation(
    @Param() { id }: GetReservationParamsDTO,
    @User() { userId }: JwtPayload,
  ): Promise<GetReservationResponseDTO> {
    const book = await this.reservationsService.findByIdOrFail(id, userId);
    return new GetReservationResponseDTO(book);
  }

  @ApiBearerAuth()
  @UseGuards(JwtAuthGuard)
  @Get()
  @ApiOkResponse({ type: GetReservationsListResponseDTO })
  async getReservationsList(@User() { userId }: JwtPayload): Promise<GetReservationsListResponseDTO> {
    const reservations = await this.reservationsService.findMany({ userId });
    return new GetReservationsListResponseDTO(reservations);
  }

  @ApiBearerAuth()
  @UseGuards(JwtAuthGuard)
  @Post()
  @ApiCreatedResponse({ type: ReserveBookResponseDTO })
  async reserveBook(
    @Body() { bookId }: ReserveBookBodyDTO,
    @User() { userId }: JwtPayload,
  ): Promise<ReserveBookResponseDTO> {
    const reservation = await this.reservationsService.create({ bookId, userId });
    return new ReserveBookResponseDTO(reservation);
  }

  @ApiBearerAuth()
  @UseGuards(JwtAuthGuard)
  @Delete(':id')
  @ApiNoContentResponse()
  async returnReservation(@Param() { id }: ReturnReservationParamsDTO, @User() { userId }: JwtPayload): Promise<void> {
    await this.reservationsService.deleteOne(id, userId);
  }
}
