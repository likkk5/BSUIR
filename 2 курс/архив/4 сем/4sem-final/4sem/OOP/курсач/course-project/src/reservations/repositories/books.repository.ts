import { Injectable } from '@nestjs/common';

import { BooksBaseRepository } from '@libs/repositories';

@Injectable()
export class BooksRepository extends BooksBaseRepository {}
