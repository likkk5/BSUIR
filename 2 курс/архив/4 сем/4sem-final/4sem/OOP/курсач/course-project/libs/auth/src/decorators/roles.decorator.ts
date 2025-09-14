import { CustomDecorator, SetMetadata } from '@nestjs/common';

import { USER_ROLE } from '@libs/constants';

export const ROLES_KEY = 'roles';
export const Roles = (...roles: USER_ROLE[]): CustomDecorator<string> => SetMetadata(ROLES_KEY, roles);
