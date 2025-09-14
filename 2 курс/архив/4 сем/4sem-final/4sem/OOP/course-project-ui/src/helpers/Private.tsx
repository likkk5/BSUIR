import React, { FC, PropsWithChildren } from 'react';
import { Navigate } from 'react-router-dom';
import { useAuth } from '../contexts/AuthContext';
import { USER_ROLE } from '../constants';
import NotAllowed from '../pages/NotAllowed';

interface PrivateProps extends PropsWithChildren {
  allowedRoles?: USER_ROLE[],
}

export const Private: FC<PrivateProps> = ({ children: Children, allowedRoles }) => {
  const { currentUser } = useAuth();

  if (!currentUser) {
    return <Navigate to="/login"/>;
  }

  if (allowedRoles && !allowedRoles.includes(currentUser.role)) {
    return <NotAllowed/>;
  }

  return <>{Children}</>;
};
