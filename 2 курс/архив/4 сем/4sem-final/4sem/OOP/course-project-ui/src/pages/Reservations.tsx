import React, { FunctionComponent, useEffect, useState } from 'react';
import { ReservationDTO } from '../types';
import { Alert, ListGroup } from 'react-bootstrap';
import ReservationService from '../services/reservation.service';
import Reservation from '../components/Reservation';

const Reservations: FunctionComponent = () => {
  const [reservations, setReservations] = useState<ReservationDTO[]>([]);

  useEffect(() => {
    const fetchReservations = async () => {
      const reservationDTOs = await ReservationService.getReservationsList();
      setReservations([...reservationDTOs.items.filter((dto) => !dto.returnedAt), ...reservationDTOs.items.filter((dto) => dto.returnedAt)]);
    };

    fetchReservations().catch(console.error);
  }, []);

  return (
    reservations.length ?
      <ListGroup>
        {reservations.map(reservation => <ListGroup.Item><Reservation reservation={reservation}/></ListGroup.Item>)}
      </ListGroup>
      :
      <Alert variant="info">No reservations</Alert>
  );

};

export default Reservations;
