import { CustomDecorator } from '@nestjs/common';

import { USER_ROLE } from '@libs/constants';

import { Roles } from './roles.decorator';

export const Admin = (): CustomDecorator<string> => Roles(USER_ROLE.ADMIN);
