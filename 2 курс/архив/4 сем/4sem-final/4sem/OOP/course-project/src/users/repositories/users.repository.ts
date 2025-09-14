import { Injectable } from '@nestjs/common';

import { UsersBaseRepository } from '@libs/repositories';

@Injectable()
export class UsersRepository extends UsersBaseRepository {}
