import { Paginated, ReservationDTO } from '../types';
import axios from '../helpers/axios';
import { RESERVATION_URL } from '../constants';
import { StatisticsDTO } from '../types/statistics.dto';

export default class ReservationService {
  static async getReservation(
    id: number,
  ): Promise<ReservationDTO> {
    const { data } = await axios.get<ReservationDTO>(RESERVATION_URL.RESERVATION_BY_ID(id));
    return data;
  }

  static async getReservationsList(): Promise<Paginated<ReservationDTO>> {
    const { data } = await axios.get<Paginated<ReservationDTO>>(RESERVATION_URL.RESERVATIONS);
    return data;
  }

  static async reserveBook(
    bookId: number,
  ): Promise<ReservationDTO> {
    const { data } = await axios.post<ReservationDTO>(RESERVATION_URL.RESERVATIONS, { bookId });
    return data;
  }

  static async returnReservation(id: number): Promise<void> {
    await axios.delete(RESERVATION_URL.RESERVATION_BY_ID(id));
  }

  static async getStatistics(): Promise<StatisticsDTO> {
    const { data } = await axios.get<StatisticsDTO>(RESERVATION_URL.STATISTICS);
    return data;
  }
}
