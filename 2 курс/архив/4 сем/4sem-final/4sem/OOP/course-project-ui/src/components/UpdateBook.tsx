import React, { FunctionComponent, useState } from 'react';
import { BookDTO } from '../types';
import { Button, Modal } from 'react-bootstrap';
import BookForm from './BookForm';
import BooksService from '../services/books.service';

interface OwnProps {
  book: BookDTO;
}

type Props = OwnProps;

const UpdateBook: FunctionComponent<Props> = ({ book }) => {

  const [show, setShow] = useState(false);

  const updateBook = async (bookToUpdate: Omit<BookDTO, 'id'>) => {
    await BooksService.updateBook(book.id, bookToUpdate);
    handleClose();
    window.location.reload();
  };

  const handleClose = () => setShow(false);
  const handleShow = () => setShow(true);

  return (
    <>
      <Button variant="primary" onClick={handleShow}>
        Update book
      </Button>

      <Modal show={show} onHide={handleClose}>
        <Modal.Header closeButton>
          <Modal.Title>Update </Modal.Title>
        </Modal.Header>
        <Modal.Body>
          <BookForm bookAction={updateBook} book={book}/>
        </Modal.Body>
        <Modal.Footer>
          <Button variant="secondary" onClick={handleClose}>
            Close
          </Button>
        </Modal.Footer>
      </Modal>
    </>);
};

export default UpdateBook;
