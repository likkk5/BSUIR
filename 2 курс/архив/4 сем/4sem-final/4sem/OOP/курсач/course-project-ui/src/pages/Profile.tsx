import React, { FunctionComponent, useEffect, useState } from 'react';
import { useAuth } from '../contexts/AuthContext';
import { Navigate } from 'react-router-dom';
import { Alert, Card, Row, Stack } from 'react-bootstrap';
import { PrivateOrEmpty } from '../helpers/PrivateOrEmpty';
import { USER_ROLE } from '../constants';
import { StatisticsDTO } from '../types/statistics.dto';
import ReservationService from '../services/reservation.service';

function Statistics() {
  const [statistics, setStatistics] = useState<StatisticsDTO>({ moneyFromRent: 0, moneyInDeposit: 0 });

  useEffect(() => {
    const fetchReservations = async () => {
      const statisticsDTO = await ReservationService.getStatistics();
      setStatistics(statisticsDTO);
    };
    fetchReservations().catch(console.error);
  }, []);

  return <Row>
    <Alert>
      <Stack>
        <Row>Money from deposits: {statistics.moneyInDeposit}</Row>
        <Row>Money from rent: {statistics.moneyFromRent}</Row>
      </Stack>
    </Alert>
  </Row>;
}

const Profile: FunctionComponent = () => {
  const { currentUser } = useAuth();


  if (!currentUser) {
    return <Navigate to="/login"/>;
  }

  return <>
    <Card>
      <Card.Body>
        <Stack direction="vertical">
          <Row>Name: {currentUser.name}</Row>
          <Row>Email: {currentUser.email}</Row>
          <PrivateOrEmpty allowedRoles={[USER_ROLE.ADMIN]}>
            <Statistics/>
          </PrivateOrEmpty>
        </Stack>
      </Card.Body>
    </Card>
  </>;
};

export default Profile;
