import React, { FunctionComponent } from 'react';

import { BookDTO } from '../types';
import { Button, Container, Row } from 'react-bootstrap';
import BooksService from '../services/books.service';
import { PrivateOrEmpty } from '../helpers/PrivateOrEmpty';
import { USER_ROLE } from '../constants';
import UpdateBook from './UpdateBook';
import ReserveBook from './ReserveBook';

const Book: FunctionComponent<{ book: BookDTO }> = ({ book }) => {
  const handleDelete: React.MouseEventHandler<HTMLElement> = () => {
    BooksService.deleteBook(book.id).catch(console.error);
    window.location.reload();
  };

  return (
    <Container fluid="sm">
      <Row><h4>{book.title}</h4></Row>
      <Row>Genre: {book.genre}</Row>
      <Row>Author: {book.author}</Row>
      <Row>Amount: {book.amount}</Row>
      <Row>Rent price: {book.rentPrice}</Row>
      <Row>Deposit price: {book.depositPrice}</Row>
      <Row>Description: {book.description}</Row>
      <Row>
        <PrivateOrEmpty>
          <ReserveBook book={book}/>
        </PrivateOrEmpty>
        <PrivateOrEmpty allowedRoles={[USER_ROLE.ADMIN]}>
          <Button className="mb-2" variant="danger" onClick={handleDelete}>Delete</Button>
          <UpdateBook book={book}/>
        </PrivateOrEmpty>
      </Row>
    </Container>
  );
};

export default Book;
