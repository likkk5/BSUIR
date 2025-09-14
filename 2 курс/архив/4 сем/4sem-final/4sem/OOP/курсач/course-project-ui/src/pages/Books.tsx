import React, { FunctionComponent, useEffect, useState } from 'react';
import { BookDTO } from '../types';
import Book from '../components/Book';
import BooksService from '../services/books.service';
import { Alert, ListGroup, Stack } from 'react-bootstrap';
import CreateBook from '../components/CreateBook';
import { PrivateOrEmpty } from '../helpers/PrivateOrEmpty';
import { USER_ROLE } from '../constants';

const Books: FunctionComponent = () => {
  const [books, setBooks] = useState<BookDTO[]>([]);

  useEffect(() => {
    const fetchBooks = async () => {
      const booksDTOs = await BooksService.getBooksList();
      setBooks(booksDTOs.items);
    };

    fetchBooks().catch(console.error);
  }, []);

  return (
    <Stack gap={3}>
      <PrivateOrEmpty allowedRoles={[USER_ROLE.ADMIN]}>
        <CreateBook/>
      </PrivateOrEmpty>
      {books.length ?
        <ListGroup>
          {books.map(book => <ListGroup.Item><Book book={book}/></ListGroup.Item>)}
        </ListGroup>
        : <Alert variant="info">No books</Alert>
      }
    </Stack>
  );

};

export default Books;
