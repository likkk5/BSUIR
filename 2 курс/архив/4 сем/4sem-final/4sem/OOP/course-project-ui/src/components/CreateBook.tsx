import React, { FunctionComponent, useState } from 'react';
import { BookDTO } from '../types';
import { Button, Modal } from 'react-bootstrap';
import BookForm from './BookForm';
import BooksService from '../services/books.service';


const CreateBook: FunctionComponent = () => {

  const [show, setShow] = useState(false);

  const createBook = async (bookToCreate: Omit<BookDTO, 'id'>) => {
    await BooksService.createBook(bookToCreate).catch(console.error);
    handleClose();
    window.location.reload();
  };

  const handleClose = () => setShow(false);
  const handleShow = () => setShow(true);

  return (
    <>
      <Button variant="success" onClick={handleShow}>
        Create book
      </Button>

      <Modal show={show} onHide={handleClose}>
        <Modal.Header closeButton>
          <Modal.Title>Create</Modal.Title>
        </Modal.Header>
        <Modal.Body>
          <BookForm bookAction={createBook}/>
        </Modal.Body>
        <Modal.Footer>
          <Button variant="secondary" onClick={handleClose}>
            Close
          </Button>
        </Modal.Footer>
      </Modal>
    </>);
};

export default CreateBook;
