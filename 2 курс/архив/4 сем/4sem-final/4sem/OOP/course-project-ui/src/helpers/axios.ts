import axios from 'axios';
import authHeader from './authHeader';


export default axios.create({ headers: { common: authHeader() } });
