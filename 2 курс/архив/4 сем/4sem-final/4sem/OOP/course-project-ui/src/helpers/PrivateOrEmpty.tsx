import React, { FC, PropsWithChildren } from 'react';
import { useAuth } from '../contexts/AuthContext';
import { USER_ROLE } from '../constants';

interface PrivateOrEmptyProps extends PropsWithChildren {
  allowedRoles?: USER_ROLE[],
}

export const PrivateOrEmpty: FC<PrivateOrEmptyProps> = ({ children: Children, allowedRoles }) => {
  const { currentUser } = useAuth();

  if (!currentUser || (allowedRoles && !allowedRoles.includes(currentUser.role))) {
    return <></>;
  }

  return <>{Children}</>;
};
