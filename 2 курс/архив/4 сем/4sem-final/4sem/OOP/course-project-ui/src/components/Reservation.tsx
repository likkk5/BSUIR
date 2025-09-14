import React, { FunctionComponent } from 'react';

import { ReservationDTO } from '../types';
import { Button, Container, Row } from 'react-bootstrap';
import { PrivateOrEmpty } from '../helpers/PrivateOrEmpty';
import ReservationService from '../services/reservation.service';

const Reservation: FunctionComponent<{ reservation: ReservationDTO }> = ({ reservation }) => {
  const handleReturn: React.MouseEventHandler<HTMLElement> = () => {
    ReservationService.returnReservation(reservation.id).catch(console.error);
    window.location.reload();
  };

  return (
    <Container fluid="sm">
      <Row><h4>{reservation.book.title}</h4></Row>
      <Row>Genre: {reservation.book.genre}</Row>
      <Row>Author: {reservation.book.author}</Row>
      {reservation.returnedAt ? <Row>Returned at: {reservation.returnedAt.toString()}</Row> :
        <Row>
          <PrivateOrEmpty>
            <Button className="mb-2" variant="outline-primary" onClick={handleReturn}>Return book</Button>
          </PrivateOrEmpty>
        </Row>}
    </Container>
  );
};

export default Reservation;
