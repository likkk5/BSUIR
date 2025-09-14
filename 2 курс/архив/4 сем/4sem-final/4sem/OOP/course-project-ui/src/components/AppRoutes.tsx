import { Route, Routes } from 'react-router-dom';
import Home from '../pages/Home';
import Signup from '../pages/Signup';
import Login from '../pages/Login';
import Profile from '../pages/Profile';
import Books from '../pages/Books';
import NotFound from '../pages/NotFound';
import { OnlyPublic } from '../helpers/OnlyPublic';
import { Private } from '../helpers/Private';
import Reservations from '../pages/Reservations';

export function AppRoutes() {
  return <Routes>
    <Route path="/" element={<Home/>}/>
    <Route path="/signup" element={<OnlyPublic><Signup/></OnlyPublic>}/>
    <Route path="/login" element={<OnlyPublic><Login/></OnlyPublic>}/>
    <Route path="/profile" element={<Profile/>}/>
    <Route path="/books" element={<Books/>}/>
    <Route path="/reservations" element={<Private><Reservations/></Private>}/>
    <Route path="*" element={<NotFound/>}/>
  </Routes>;
}
