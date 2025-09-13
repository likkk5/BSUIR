using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using HotelManagementSystem.Data;
using HotelManagementSystem.Models;
using Npgsql;

namespace HotelManagementSystem.Services
{
    public class ReservationService
    {
        private readonly DatabaseManager _dbManager;

        public ReservationService(DatabaseManager dbManager)
        {
            _dbManager = dbManager;
        }

        public List<Reservation> GetAllReservations()
        {
            var reservations = new List<Reservation>();
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = "SELECT * FROM reservation";
                using (var command = new NpgsqlCommand(sql, connection))
                using (var reader = command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        reservations.Add(new Reservation
                        {
                            Id = (int)reader["id"],
                            ReservationDate = (DateTime)reader["reservation_date"],
                            CheckInDate = (DateTime)reader["check_in_date"],
                            CheckOutDate = (DateTime)reader["check_out_date"],
                            ReservationStatus = reader["reservation_status"].ToString(),
                            RoomNumber = reader["room_number"]?.ToString() ?? string.Empty,
                            GuestId = Convert.ToInt32(reader["guest_id"]),
                            Cost = (decimal)reader["cost"]
                        });
                    }
                }
            }
            return reservations;
        }

        public Reservation GetReservationById(int id)
        {
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = "SELECT * FROM reservation WHERE id = @Id";
                using (var command = new NpgsqlCommand(sql, connection))
                {
                    command.Parameters.AddWithValue("@Id", id);
                    using (var reader = command.ExecuteReader())
                    {
                        if (reader.Read())
                        {
                            return new Reservation
                            {
                                Id = (int)reader["id"],
                                ReservationDate = (DateTime)reader["reservation_date"],
                                CheckInDate = (DateTime)reader["check_in_date"],
                                CheckOutDate = (DateTime)reader["check_out_date"],
                                ReservationStatus = reader["reservation_status"].ToString(),
                                RoomNumber = reader["room_number"]?.ToString() ?? string.Empty,
                                GuestId = (int)reader["guest_id"],
                                Cost = (decimal)reader["cost"]
                            };
                        }
                    }
                }
            }
            return null;
        }

        public void AddReservation(Reservation reservation)
        {
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = @"
                    INSERT INTO reservation (reservation_date, check_in_date, check_out_date, 
                                             reservation_status, room_number, guest_id, cost) 
                    VALUES (@ReservationDate, @CheckInDate, @CheckOutDate, @ReservationStatus, 
                            @RoomNumber, @GuestId, @Cost)";
                using (var command = new NpgsqlCommand(sql, connection))
                {
                    command.Parameters.AddWithValue("@ReservationDate", reservation.ReservationDate);
                    command.Parameters.AddWithValue("@CheckInDate", reservation.CheckInDate);
                    command.Parameters.AddWithValue("@CheckOutDate", reservation.CheckOutDate);
                    command.Parameters.AddWithValue("@ReservationStatus", reservation.ReservationStatus);
                    command.Parameters.AddWithValue("@RoomNumber", reservation.RoomNumber);
                    command.Parameters.AddWithValue("@GuestId", reservation.GuestId);
                    command.Parameters.AddWithValue("@Cost", reservation.Cost);
                    command.ExecuteNonQuery();
                }
            }
        }

        public void UpdateReservation(Reservation reservation)
        {
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = @"
                    UPDATE reservation 
                    SET reservation_date = @ReservationDate, check_in_date = @CheckInDate, 
                        check_out_date = @CheckOutDate, reservation_status = @ReservationStatus, 
                        room_number = @RoomNumber, guest_id = @GuestId, cost = @Cost 
                    WHERE id = @Id";
                using (var command = new NpgsqlCommand(sql, connection))
                {
                    command.Parameters.AddWithValue("@ReservationDate", reservation.ReservationDate);
                    command.Parameters.AddWithValue("@CheckInDate", reservation.CheckInDate);
                    command.Parameters.AddWithValue("@CheckOutDate", reservation.CheckOutDate);
                    command.Parameters.AddWithValue("@ReservationStatus", reservation.ReservationStatus);
                    command.Parameters.AddWithValue("@RoomNumber", reservation.RoomNumber);
                    command.Parameters.AddWithValue("@GuestId", reservation.GuestId);
                    command.Parameters.AddWithValue("@Cost", reservation.Cost);
                    command.Parameters.AddWithValue("@Id", reservation.Id);
                    command.ExecuteNonQuery();
                }
            }
        }

        public void DeleteReservation(int id)
        {
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = "DELETE FROM reservation WHERE id = @Id";
                using (var command = new NpgsqlCommand(sql, connection))
                {
                    command.Parameters.AddWithValue("@Id", id);
                    command.ExecuteNonQuery();
                }
            }
        }
        public List<Reservation> GetReservationsByUser(int userId)
        {
            var reservations = new List<Reservation>();
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();

                // Получаем guest_id по userId
                string guestQuery = "SELECT id FROM guest WHERE user_id = @userId";
                int guestId;

                using (var guestCommand = new NpgsqlCommand(guestQuery, connection))
                {
                    guestCommand.Parameters.AddWithValue("@userId", userId);
                    var result = guestCommand.ExecuteScalar();
                    if (result == null)
                    {
                        return reservations; // Возвращаем пустой список, если гость не найден
                    }
                    guestId = (int)result;
                }

                // Явное указание столбцов
                string query = @"
            SELECT 
                id, reservation_date, check_in_date, check_out_date, 
                reservation_status, room_number, guest_id, cost 
            FROM reservation 
            WHERE guest_id = @guestId 
            ORDER BY check_in_date DESC";

                using (var command = new NpgsqlCommand(query, connection))
                {
                    command.Parameters.AddWithValue("@guestId", guestId);
                    using (var reader = command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            reservations.Add(new Reservation
                            {
                                Id = reader.GetInt32(0),                        // Поле id
                                ReservationDate = reader.GetDateTime(1),        // Поле reservation_date
                                CheckInDate = reader.GetDateTime(2),            // Поле check_in_date
                                CheckOutDate = reader.GetDateTime(3),           // Поле check_out_date
                                ReservationStatus = reader.GetString(4),        // Поле reservation_status
                                RoomNumber = reader.GetString(5),               // Поле room_number
                                GuestId = reader.GetInt32(6),                   // Поле guest_id
                                Cost = reader.GetDecimal(7)                     // Поле cost
                            });
                        }
                    }
                }
            }
            return reservations;
        }
        public void CancelReservationProcedure(int reservationId, int guestId)
        {
            try
            {
                using var connection = _dbManager.GetConnection();
                connection.Open();

                using var command = new NpgsqlCommand("CALL cancel_reservation(@reservation_id, @guest_id)", connection);
                command.Parameters.AddWithValue("@reservation_id", reservationId);
                command.Parameters.AddWithValue("@guest_id", guestId);
                command.ExecuteNonQuery();
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка при вызове процедуры отмены бронирования: {ex.Message}");
                throw;
            }
        }

    }
}
