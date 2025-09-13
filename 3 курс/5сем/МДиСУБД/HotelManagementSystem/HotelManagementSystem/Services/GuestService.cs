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
    public class GuestService
    {
        private readonly DatabaseManager _dbManager;

        public GuestService(DatabaseManager dbManager)
        {
            _dbManager = dbManager;
        }

        public List<Guest> GetAllGuests()
        {
            var guests = new List<Guest>();
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = "SELECT * FROM guest";
                using (var command = new NpgsqlCommand(sql, connection))
                using (var reader = command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        guests.Add(new Guest
                        {
                            Id = (int)reader["id"],
                            UserId = (int)reader["user_id"],
                            PassportNumber = reader["passport_number"].ToString(),
                            Residence = reader["residence"]?.ToString()
                        });
                    }
                }
            }
            return guests;
        }

        public Guest GetGuestById(int id)
        {
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = "SELECT * FROM guest WHERE id = @Id";
                using (var command = new NpgsqlCommand(sql, connection))
                {
                    command.Parameters.AddWithValue("@Id", id);
                    using (var reader = command.ExecuteReader())
                    {
                        if (reader.Read())
                        {
                            return new Guest
                            {
                                Id = (int)reader["id"],
                                UserId = (int)reader["user_id"],
                                PassportNumber = reader["passport_number"].ToString(),
                                Residence = reader["residence"]?.ToString()
                            };
                        }
                    }
                }
            }
            return null;
        }

        public void AddGuest(Guest guest)
        {
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = @"
                    INSERT INTO guest (user_id, passport_number, residence) 
                    VALUES (@UserId, @PassportNumber, @Residence)";
                using (var command = new NpgsqlCommand(sql, connection))
                {
                    command.Parameters.AddWithValue("@UserId", guest.UserId);
                    command.Parameters.AddWithValue("@PassportNumber", guest.PassportNumber);
                    command.Parameters.AddWithValue("@Residence", (object)guest.Residence ?? DBNull.Value);
                    command.ExecuteNonQuery();
                }
            }
        }

        public void UpdateGuest(Guest guest)
        {
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = @"
                    UPDATE guest 
                    SET user_id = @UserId, passport_number = @PassportNumber, residence = @Residence 
                    WHERE id = @Id";
                using (var command = new NpgsqlCommand(sql, connection))
                {
                    command.Parameters.AddWithValue("@UserId", guest.UserId);
                    command.Parameters.AddWithValue("@PassportNumber", guest.PassportNumber);
                    command.Parameters.AddWithValue("@Residence", (object)guest.Residence ?? DBNull.Value);
                    command.Parameters.AddWithValue("@Id", guest.Id);
                    command.ExecuteNonQuery();
                }
            }
        }

        public void DeleteGuest(int id)
        {
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = "DELETE FROM guest WHERE id = @Id";
                using (var command = new NpgsqlCommand(sql, connection))
                {
                    command.Parameters.AddWithValue("@Id", id);
                    command.ExecuteNonQuery();
                }
            }
        }
        public int GetGuestIdByUserId(int userId)
        {
            if (_dbManager == null)
            {
                Console.WriteLine("Ошибка: DatabaseManager не инициализирован.");
                return 0; // Возвращаем 0 как значение по умолчанию
            }

            try
            {
                using (var connection = _dbManager.GetConnection())
                {
                    connection.Open();
                    Console.WriteLine("Соединение с базой данных установлено.");

                    string sql = "SELECT id FROM guest WHERE user_id = @UserId";
                    using (var command = new NpgsqlCommand(sql, connection))
                    {
                        command.Parameters.AddWithValue("@UserId", userId);
                        Console.WriteLine($"Выполняется запрос: {sql} с параметром userId = {userId}");

                        using (var reader = command.ExecuteReader())
                        {
                            if (reader.Read())
                            {
                                var idValue = reader["id"];
                                Console.WriteLine($"Получен результат: id = {idValue}");

                                if (idValue != DBNull.Value)
                                {
                                    return Convert.ToInt32(idValue);
                                }
                            }
                            else
                            {
                                Console.WriteLine("Результаты отсутствуют.");
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка при выполнении метода GetGuestIdByUserId: {ex.Message}");
                Console.WriteLine($"Трассировка стека: {ex.StackTrace}");
            }

            Console.WriteLine("Возвращается значение 0, так как запись не найдена или произошла ошибка.");
            return 0; // Если запись не найдена или произошла ошибка
        }




    }
}
