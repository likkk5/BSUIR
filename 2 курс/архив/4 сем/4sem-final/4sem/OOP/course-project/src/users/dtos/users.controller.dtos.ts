import { ApiProperty } from '@nestjs/swagger';
import { Expose, plainToClass } from 'class-transformer';

import { ApiPropertyEnum, ApiPropertyId, ApiPropertyString } from '@libs/api-decorators';
import { UserEntity } from '@libs/entities';
import { USER_ROLE } from '@libs/constants';

export class UserDTO {
  @Expose()
  @ApiPropertyId()
  id!: number;

  @Expose()
  @ApiPropertyString()
  name!: string;

  @Expose()
  @ApiPropertyString()
  email!: string;

  @Expose()
  @ApiPropertyEnum(USER_ROLE)
  role!: USER_ROLE;

  constructor(data: UserEntity) {
    Object.assign(this, plainToClass(UserDTO, data, { excludeExtraneousValues: true }));
  }
}

export class GetUsersListResponseDTO {
  @Expose()
  @ApiProperty({ type: [UserDTO] })
  items: UserDTO[];

  constructor(userEntities: UserEntity[]) {
    this.items = userEntities.map((entity) => new UserDTO(entity));
  }
}

export class GetUserParamsDTO {
  @ApiPropertyId()
  id!: number;
}

export class GetUserResponseDTO extends UserDTO {}
