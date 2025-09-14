import React, { FunctionComponent, useState } from 'react';
import { BookDTO } from '../types';
import { Button, Modal } from 'react-bootstrap';
import ReservationService from '../services/reservation.service';

interface OwnProps {
  book: BookDTO;
}

type Props = OwnProps;

const ReserveBook: FunctionComponent<Props> = ({ book }) => {

  const [show, setShow] = useState(false);
  const [error, setError] = useState(false);

  const reserveBook = async () => {
    if (book.amount <= 0) {
      setError(true);
      return;
    }

    await ReservationService.reserveBook(book.id);
    setShow(true);
  };

  const handleCloseErr = () => setError(false);
  const handleClose = () => {
    setShow(false);
    window.location.reload();
  };

  return (
    <>
      <Button variant="outline-success" className="mb-2" onClick={reserveBook}>
        Reserve book
      </Button>

      <Modal show={error} onHide={handleCloseErr}>
        <Modal.Header closeButton>
          <Modal.Title>Cannot reserve book</Modal.Title>
        </Modal.Header>
        <Modal.Footer>
          <Button variant="secondary" onClick={handleCloseErr}>
            Close
          </Button>
        </Modal.Footer>
      </Modal>

      <Modal show={show} onHide={handleClose}>
        <Modal.Header closeButton>
          <Modal.Title>Successfully reserved</Modal.Title>
        </Modal.Header>
        <Modal.Footer>
          <Button variant="secondary" onClick={handleClose}>
            Close
          </Button>
        </Modal.Footer>
      </Modal>
    </>);
};

export default ReserveBook;
