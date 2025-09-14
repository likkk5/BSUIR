import React, { FunctionComponent, useEffect } from 'react';
import { useNavigate } from 'react-router-dom';
import { Alert } from 'react-bootstrap';

interface OwnProps {
}

type Props = OwnProps;

const NotAllowed: FunctionComponent<Props> = (props) => {
  const navigate = useNavigate();

  useEffect(() => {
    setTimeout(() => {
      navigate('/');
    }, 100);
  }, []);

  return <Alert variant="danger">Action not allowed</Alert>;
};

export default NotAllowed;
