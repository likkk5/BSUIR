import { ApiProperty, PickType } from '@nestjs/swagger';
import { Expose, plainToClass, Type } from 'class-transformer';

import { ApiPropertyDate, ApiPropertyId, ApiPropertyNumber, ApiPropertyString } from '@libs/api-decorators';
import { BookEntity, ReservationEntity } from '@libs/entities';

export class BookDTO {
  @Expose()
  @ApiPropertyId()
  id!: number;

  @Expose()
  @ApiPropertyString()
  title!: string;

  @Expose()
  @ApiPropertyString()
  genre!: string;

  @Expose()
  @ApiPropertyString()
  author!: string;

  @Expose()
  @ApiPropertyNumber()
  depositPrice!: number;

  @Expose()
  @ApiPropertyNumber()
  amount!: number;

  @Expose()
  @ApiPropertyNumber()
  rentPrice!: number;

  constructor(data: BookEntity) {
    Object.assign(this, plainToClass(BookDTO, data, { excludeExtraneousValues: true }));
  }
}

export class ReservationDTO {
  @Expose()
  @ApiPropertyId()
  id!: number;

  @Expose()
  @Type(() => BookDTO)
  book!: BookDTO;

  @Expose()
  @ApiPropertyId()
  bookId!: number;

  @Expose()
  @ApiPropertyString()
  description!: string;

  @Expose()
  @ApiPropertyId()
  userId!: number;

  @Expose()
  @ApiPropertyDate()
  expectedReturnDate!: Date;

  @Expose()
  @ApiPropertyDate()
  returnedAt!: Date;

  constructor(data: ReservationEntity) {
    if (data) {
      this.book = new BookDTO(data.book);
    }
    Object.assign(this, plainToClass(ReservationDTO, data, { excludeExtraneousValues: true }));
  }
}

export class GetReservationsListResponseDTO {
  @Expose()
  @ApiProperty({ type: [ReservationDTO] })
  items: ReservationDTO[];

  constructor(entities: ReservationEntity[]) {
    this.items = entities.map((entity) => new ReservationDTO(entity));
  }
}

export class GetReservationParamsDTO {
  @ApiPropertyId()
  id!: number;
}

export class GetReservationResponseDTO extends ReservationDTO {}

export class ReserveBookBodyDTO extends PickType(ReservationDTO, ['bookId']) {}

export class ReserveBookResponseDTO extends ReservationDTO {}

export class ReturnReservationParamsDTO extends GetReservationParamsDTO {}

export class GetStatisticsResponseDTO {
  @Expose()
  @ApiPropertyNumber()
  moneyInDeposit!: number;

  @Expose()
  @ApiPropertyNumber()
  moneyFromRent!: number;

  constructor(data: GetStatisticsResponseDTO) {
    Object.assign(this, plainToClass(GetStatisticsResponseDTO, data, { excludeExtraneousValues: true }));
  }
}
