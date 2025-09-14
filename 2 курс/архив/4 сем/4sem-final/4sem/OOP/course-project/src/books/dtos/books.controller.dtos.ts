import { ApiProperty, OmitType, PartialType } from '@nestjs/swagger';
import { Expose, plainToClass } from 'class-transformer';

import { ApiPropertyId, ApiPropertyNumber, ApiPropertyString } from '@libs/api-decorators';
import { BookEntity } from '@libs/entities';

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
  @ApiPropertyString()
  description!: string;

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

export class GetBooksListQueryDTO {
  @ApiPropertyString({ isOptional: true, trim: true })
  search?: string;
}

export class GetBooksListResponseDTO {
  @Expose()
  @ApiProperty({ type: [BookDTO] })
  items: BookDTO[];

  constructor(bookEntities: BookEntity[]) {
    this.items = bookEntities.map((entity) => new BookDTO(entity));
  }
}

export class GetBookParamsDTO {
  @ApiPropertyId()
  id!: number;
}

export class GetBookResponseDTO extends BookDTO {}

export class CreateBookBodyDTO extends OmitType(BookDTO, ['id']) {}

export class CreateBookResponseDTO extends BookDTO {}

export class UpdateBookParamsDTO extends GetBookParamsDTO {}

export class UpdateBookBodyDTO extends PartialType(CreateBookBodyDTO) {}

export class UpdateBookResponseDTO extends BookDTO {}

export class DeleteBookParamsDTO extends GetBookParamsDTO {}
