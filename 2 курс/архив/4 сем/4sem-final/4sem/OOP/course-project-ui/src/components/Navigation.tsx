import React, { FunctionComponent } from 'react';
import { Button, Container, Nav, Navbar } from 'react-bootstrap';
import { useAuth } from '../contexts/AuthContext';
import { useNavigate } from 'react-router-dom';
import { PrivateOrEmpty } from '../helpers/PrivateOrEmpty';


const Navigation: FunctionComponent = () => {

  const { currentUser, logout } = useAuth();
  const navigate = useNavigate();

  const handleClick = () => navigate('/login');

  return (
    <Navbar bg="light" expand="lg">
      <Container>
        <Navbar.Brand href="/">Library</Navbar.Brand>
        <Navbar.Toggle aria-controls="basic-navbar-nav"/>
        <Navbar.Collapse>
          <Nav className="me-auto">
            <Nav.Link href="/">Home</Nav.Link>
            <PrivateOrEmpty>
              <Nav.Link href="/reservations">Reservations</Nav.Link>
              <Nav.Link href="/profile">Profile</Nav.Link>
            </PrivateOrEmpty>
          </Nav>
        </Navbar.Collapse>
        {currentUser ? <Button variant="outline-success" onClick={logout}>Log out</Button> :
          <Button onClick={handleClick} type="button">Log in</Button>}
      </Container>

    </Navbar>);
};

export default Navigation;
