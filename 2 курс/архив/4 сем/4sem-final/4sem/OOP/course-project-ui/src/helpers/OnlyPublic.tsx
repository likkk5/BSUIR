import React, { FC, PropsWithChildren } from 'react';
import { Navigate } from 'react-router-dom';
import { useAuth } from '../contexts/AuthContext';

interface Props extends PropsWithChildren {
}

export const OnlyPublic: FC<Props> = ({ children: Children }) => {
  const { currentUser } = useAuth();

  if (currentUser) {
    return <Navigate to="/"/>;
  }

  return <>{Children}</>;
};
