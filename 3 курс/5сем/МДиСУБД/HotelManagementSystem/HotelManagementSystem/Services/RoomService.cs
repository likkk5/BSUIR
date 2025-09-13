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
    public class RoomService
    {
        private readonly DatabaseManager _dbManager;

        public RoomService(DatabaseManager dbManager)
        {
            _dbManager = dbManager;
        }

        public List<Room> GetAllRooms()
        {
            var rooms = new List<Room>();
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = "SELECT * FROM room";
                using (var command = new NpgsqlCommand(sql, connection))
                using (var reader = command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        rooms.Add(new Room
                        {
                            Id = (int)reader["id"],
                            RoomNumber = reader["room_number"].ToString(),
                            RoomType = reader["room_type"].ToString(),
                            CostForNight = (decimal)reader["cost_for_night"],
                            RoomStatus = reader["room_status"].ToString(),
                            Photo = reader["photo"] as byte[]
                        });
                    }
                }
            }
            return rooms;
        }

        public Room GetRoomById(int id)
        {
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = "SELECT * FROM room WHERE id = @Id";
                using (var command = new NpgsqlCommand(sql, connection))
                {
                    command.Parameters.AddWithValue("@Id", id);
                    using (var reader = command.ExecuteReader())
                    {
                        if (reader.Read())
                        {
                            return new Room
                            {
                                Id = (int)reader["id"],
                                RoomNumber = reader["room_number"].ToString(),
                                RoomType = reader["room_type"].ToString(),
                                CostForNight = (decimal)reader["cost_for_night"],
                                RoomStatus = reader["room_status"].ToString(),
                                Photo = reader["photo"] as byte[]
                            };
                        }
                    }
                }
            }
            return null;
        }

        public void AddRoom(Room room)
        {
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = @"
                    INSERT INTO room (room_number, room_type, cost_for_night, room_status, photo) 
                    VALUES (@RoomNumber, @RoomType, @CostForNight, @RoomStatus, @Photo)";
                using (var command = new NpgsqlCommand(sql, connection))
                {
                    command.Parameters.AddWithValue("@RoomNumber", room.RoomNumber);
                    command.Parameters.AddWithValue("@RoomType", room.RoomType);
                    command.Parameters.AddWithValue("@CostForNight", room.CostForNight);
                    command.Parameters.AddWithValue("@RoomStatus", room.RoomStatus);
                    command.Parameters.AddWithValue("@Photo", (object)room.Photo ?? DBNull.Value);
                    command.ExecuteNonQuery();
                }
            }
        }

        public void UpdateRoom(Room room)
        {
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = @"
                    UPDATE room 
                    SET room_number = @RoomNumber, room_type = @RoomType, cost_for_night = @CostForNight, 
                        room_status = @RoomStatus, photo = @Photo 
                    WHERE id = @Id";
                using (var command = new NpgsqlCommand(sql, connection))
                {
                    command.Parameters.AddWithValue("@RoomNumber", room.RoomNumber);
                    command.Parameters.AddWithValue("@RoomType", room.RoomType);
                    command.Parameters.AddWithValue("@CostForNight", room.CostForNight);
                    command.Parameters.AddWithValue("@RoomStatus", room.RoomStatus);
                    command.Parameters.AddWithValue("@Photo", (object)room.Photo ?? DBNull.Value);
                    command.Parameters.AddWithValue("@Id", room.Id);
                    command.ExecuteNonQuery();
                }
            }
        }

        public void DeleteRoom(int id)
        {
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = "DELETE FROM room WHERE id = @Id";
                using (var command = new NpgsqlCommand(sql, connection))
                {
                    command.Parameters.AddWithValue("@Id", id);
                    command.ExecuteNonQuery();
                }
            }
        }
        public List<Room> GetAvailableRooms()
        {
            var availableRooms = new List<Room>();
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string query = @"
            SELECT id, room_number, room_type, cost_for_night, room_status
            FROM room
            WHERE room_status = 'Available'";
                using (var command = new NpgsqlCommand(query, connection))
                {
                    using (var reader = command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            availableRooms.Add(new Room
                            {
                                Id = reader.GetInt32(0),
                                RoomNumber = reader.GetString(1),
                                RoomType = reader.GetString(2),
                                CostForNight = reader.GetDecimal(3),
                                RoomStatus = reader.GetString(4),
                            });
                        }
                    }
                }
            }
            return availableRooms;
        }
        public List<Room> GetRoomsForCleaning()
        {
            var cleaningRooms = new List<Room>();
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string query = @"
            SELECT id, room_number, room_type, cost_for_night, room_status, photo
            FROM room
            WHERE room_status = 'Cleaning'";
                using (var command = new NpgsqlCommand(query, connection))
                {
                    using (var reader = command.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            cleaningRooms.Add(new Room
                            {
                                Id = reader.GetInt32(0),
                                RoomNumber = reader.GetString(1),
                                RoomType = reader.GetString(2),
                                CostForNight = reader.GetDecimal(3),
                                RoomStatus = reader.GetString(4),
                                Photo = reader.IsDBNull(5) ? null : (byte[])reader["photo"]
                            });
                        }
                    }
                }
            }
            return cleaningRooms;
        }
        // Метод для вычисления стоимости бронирования
        public decimal CalculateBookingCost(string roomNumber, DateTime checkInDate, DateTime checkOutDate)
        {
            var room = GetRoomByNumber(roomNumber);
            if (room == null)
            {
                Console.WriteLine("Комната с таким номером не найдена.");
                return 0;
            }

            // Рассчитываем количество дней
            int stayDuration = (checkOutDate - checkInDate).Days;

            //// Если количество дней меньше или равно нулю, это ошибка
            //if (stayDuration <= 0)
            //{
            //    Console.WriteLine("Ошибка: дата выезда должна быть позже даты заселения.");
            //    return 0;
            //}

            // Рассчитываем стоимость бронирования
            decimal totalCost = room.CostForNight * stayDuration;
            return totalCost;
        }

        // Метод для получения комнаты по номеру
        public Room GetRoomByNumber(string roomNumber)
        {
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = "SELECT * FROM room WHERE room_number = @RoomNumber";
                using (var command = new NpgsqlCommand(sql, connection))
                {
                    command.Parameters.AddWithValue("@RoomNumber", roomNumber);
                    using (var reader = command.ExecuteReader())
                    {
                        if (reader.Read())
                        {
                            return new Room
                            {
                                Id = (int)reader["id"],
                                RoomNumber = reader["room_number"].ToString(),
                                RoomType = reader["room_type"].ToString(),
                                CostForNight = (decimal)reader["cost_for_night"],
                                RoomStatus = reader["room_status"].ToString(),
                                Photo = reader["photo"] as byte[]
                            };
                        }
                    }
                }
            }
            return null;
        }
        public List<Room> GetAvailableRoomsProcedure(DateTime checkInDate, DateTime checkOutDate)
        {
            var availableRooms = new List<Room>();

            try
            {
                using var connection = _dbManager.GetConnection();
                connection.Open();

                // Вызов процедуры
                using var command = new NpgsqlCommand("CALL get_available_rooms(@check_in_date, @check_out_date)", connection);
                command.Parameters.AddWithValue("@check_in_date", NpgsqlTypes.NpgsqlDbType.Date, checkInDate.Date);
                command.Parameters.AddWithValue("@check_out_date", NpgsqlTypes.NpgsqlDbType.Date, checkOutDate.Date);
                command.ExecuteNonQuery();

                // Чтение из временной таблицы (если процедура записывает туда данные)
                using var tempTableCommand = new NpgsqlCommand("SELECT room_number, room_type FROM temp_available_rooms", connection);
                using var reader = tempTableCommand.ExecuteReader();

                while (reader.Read())
                {
                    availableRooms.Add(new Room
                    {
                        RoomNumber = reader["room_number"].ToString(),
                        RoomType = reader["room_type"].ToString()
                    });
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка при получении доступных номеров: {ex.Message}");
                throw;
            }

            return availableRooms;
        }
    }

}
