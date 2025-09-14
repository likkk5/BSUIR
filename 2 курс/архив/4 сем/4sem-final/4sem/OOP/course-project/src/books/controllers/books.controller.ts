import { Body, Controller, Delete, Get, Param, Patch, Post, Query, UseGuards } from '@nestjs/common';
import { ApiBearerAuth, ApiCreatedResponse, ApiNoContentResponse, ApiOkResponse, ApiTags } from '@nestjs/swagger';

import { Admin, JwtAuthGuard } from '@libs/auth';

import { BooksService } from '../services';
import {
  CreateBookBodyDTO,
  CreateBookResponseDTO,
  DeleteBookParamsDTO,
  GetBookParamsDTO,
  GetBookResponseDTO,
  GetBooksListQueryDTO,
  GetBooksListResponseDTO,
  UpdateBookBodyDTO,
  UpdateBookParamsDTO,
  UpdateBookResponseDTO,
} from '../dtos';

@ApiTags('books')
@Controller('books')
export class BooksController {
  constructor(private readonly booksService: BooksService) {}

  @Get(':id')
  @ApiOkResponse({ type: GetBookResponseDTO })
  async getBook(@Param() { id }: GetBookParamsDTO): Promise<GetBookResponseDTO> {
    const book = await this.booksService.findByIdOrFail(id);
    return new GetBookResponseDTO(book);
  }

  @Get()
  @ApiOkResponse({ type: GetBooksListResponseDTO })
  async getBooksList(@Query() query: GetBooksListQueryDTO): Promise<GetBooksListResponseDTO> {
    const books = await this.booksService.findMany(query);
    return new GetBooksListResponseDTO(books);
  }

  @ApiBearerAuth()
  @UseGuards(JwtAuthGuard)
  @Admin()
  @Post()
  @ApiCreatedResponse({ type: CreateBookResponseDTO })
  async createBook(@Body() bookToCreate: CreateBookBodyDTO): Promise<CreateBookResponseDTO> {
    const book = await this.booksService.create(bookToCreate);
    return new CreateBookResponseDTO(book);
  }

  @ApiBearerAuth()
  @UseGuards(JwtAuthGuard)
  @Admin()
  @Patch(':id')
  @ApiOkResponse({ type: UpdateBookResponseDTO })
  async updateBook(
    @Param() { id }: UpdateBookParamsDTO,
    @Body() bookProps: UpdateBookBodyDTO,
  ): Promise<UpdateBookResponseDTO> {
    const book = await this.booksService.updateOne(id, bookProps);
    return new UpdateBookResponseDTO(book);
  }

  @ApiBearerAuth()
  @UseGuards(JwtAuthGuard)
  @Admin()
  @Delete(':id')
  @ApiNoContentResponse()
  async deleteBook(@Param() { id }: DeleteBookParamsDTO): Promise<void> {
    await this.booksService.deleteOne(id);
  }
}
