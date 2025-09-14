import React, { useContext, useEffect, useState } from 'react';
import AuthService from '../services/auth.service';
import { UserDTO } from '../types';
import UsersService from '../services/users.service';

interface IAuthContext {
  currentUser: UserDTO | null,
  login: (payload: { email: string, password: string }) => Promise<void>,
  signup: (payload: (Omit<UserDTO, 'id' | 'role'> & { password: string })) => Promise<void>,
  logout: () => void
}

const AuthContext = React.createContext<IAuthContext>(undefined!);

export function useAuth() {
  return useContext(AuthContext);
}

export function AuthProvider({ children }: any) {
  const [currentUser, setCurrentUser] = useState<UserDTO | null>(null);
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    const effect = async () => {
      const user = await UsersService.getSelf();
      setCurrentUser(user);
      setLoading(false);
    };
    effect().catch(console.error);
  }, []);


  async function signup(payload: Omit<UserDTO, 'id' | 'role'> & { password: string }) {
    setLoading(true);
    await AuthService.signup(payload);
    const user = await UsersService.getSelf();
    setCurrentUser(user);
    setLoading(false);
  }

  async function login(payload: { email: string, password: string }) {
    setLoading(true);
    await AuthService.login(payload);
    const user = await UsersService.getSelf();
    setCurrentUser(user);
    setLoading(false);
  }

  function logout() {
    setLoading(true);
    AuthService.logout();
    setCurrentUser(null);
    setLoading(false);
  }

  const value = {
    currentUser,
    login,
    signup,
    logout,
  };

  return (
    <AuthContext.Provider value={value}>
      {!loading && children}
    </AuthContext.Provider>
  );
}
