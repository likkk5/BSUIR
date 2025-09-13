using System;
using System.Collections.Generic;
using HotelManagementSystem.Data;
using HotelManagementSystem.Models;
using Npgsql;

namespace HotelManagementSystem.Services
{
    public class UserService
    {
        private readonly DatabaseManager _dbManager;

        public UserService(DatabaseManager dbManager)
        {
            _dbManager = dbManager;
        }

        public List<User> GetAllUsers()
        {
            var users = new List<User>();
            using var connection = _dbManager.GetConnection();
            connection.Open();
            string sql = "SELECT * FROM \"user\"";
            using var command = new NpgsqlCommand(sql, connection);
            using var reader = command.ExecuteReader();
            while (reader.Read())
            {
                users.Add(new User
                {
                    Id = (int)reader["id"],
                    FirstName = reader["first_name"].ToString(),
                    LastName = reader["last_name"].ToString(),
                    Login = reader["login"].ToString(),
                    Password = reader["password"].ToString(),
                    RoleId = (int)reader["role_id"],
                    PhoneNumber = reader["phone_number"]?.ToString(),
                    Email = reader["email"].ToString()
                });
            }
            return users;
        }

        public User GetUserById(int id)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();
            string sql = "SELECT * FROM \"user\" WHERE id = @Id";
            using var command = new NpgsqlCommand(sql, connection);
            command.Parameters.AddWithValue("@Id", id);
            using var reader = command.ExecuteReader();
            if (reader.Read())
            {
                return new User
                {
                    Id = (int)reader["id"],
                    FirstName = reader["first_name"].ToString(),
                    LastName = reader["last_name"].ToString(),
                    Login = reader["login"].ToString(),
                    Password = reader["password"].ToString(),
                    RoleId = (int)reader["role_id"],
                    PhoneNumber = reader["phone_number"]?.ToString(),
                    Email = reader["email"].ToString()
                };
            }
            return null;
        }

        //public void AddUser(User user)
        //{
        //    using var connection = _dbManager.GetConnection();
        //    connection.Open();
        //    var command = new NpgsqlCommand(
        //        "INSERT INTO \"user\" (first_name, last_name, login, password, role_id, phone_number, email) " +
        //        "VALUES (@first_name, @last_name, @login, @password, @role_id, @phone_number, @email)", connection);
        //    command.Parameters.AddWithValue("@first_name", user.FirstName);
        //    command.Parameters.AddWithValue("@last_name", user.LastName);
        //    command.Parameters.AddWithValue("@login", user.Login);
        //    command.Parameters.AddWithValue("@password", user.Password);
        //    command.Parameters.AddWithValue("@role_id", user.RoleId);
        //    command.Parameters.AddWithValue("@phone_number", (object)user.PhoneNumber ?? DBNull.Value);
        //    command.Parameters.AddWithValue("@email", user.Email);
        //    command.ExecuteNonQuery();
        //}
        public int AddUser(User user)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand(
                "INSERT INTO \"user\" (first_name, last_name, login, password, role_id, phone_number, email) " +
                "VALUES (@first_name, @last_name, @login, @password, @role_id, @phone_number, @email) " +
                "RETURNING id", connection); // Добавлено RETURNING id
            command.Parameters.AddWithValue("@first_name", user.FirstName);
            command.Parameters.AddWithValue("@last_name", user.LastName);
            command.Parameters.AddWithValue("@login", user.Login);
            command.Parameters.AddWithValue("@password", user.Password);
            command.Parameters.AddWithValue("@role_id", user.RoleId);
            command.Parameters.AddWithValue("@phone_number", (object)user.PhoneNumber ?? DBNull.Value);
            command.Parameters.AddWithValue("@email", user.Email);

            // Получаем ID нового пользователя
            int newUserId = (int)command.ExecuteScalar();
            return newUserId;
        }

        public void UpdateUser(User user)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand(
                "UPDATE \"user\" SET first_name = @first_name, last_name = @last_name, login = @login, " +
                "password = @password, role_id = @role_id, phone_number = @phone_number, email = @email " +
                "WHERE id = @id", connection);
            command.Parameters.AddWithValue("@id", user.Id);
            command.Parameters.AddWithValue("@first_name", user.FirstName);
            command.Parameters.AddWithValue("@last_name", user.LastName);
            command.Parameters.AddWithValue("@login", user.Login);
            command.Parameters.AddWithValue("@password", user.Password);
            command.Parameters.AddWithValue("@role_id", user.RoleId);
            command.Parameters.AddWithValue("@phone_number", (object)user.PhoneNumber ?? DBNull.Value);
            command.Parameters.AddWithValue("@email", user.Email);
            command.ExecuteNonQuery();
        }

        public void DeleteUser(int id)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();
            string sql = "DELETE FROM \"user\" WHERE id = @Id";
            using var command = new NpgsqlCommand(sql, connection);
            command.Parameters.AddWithValue("@Id", id);
            command.ExecuteNonQuery();
        }
        public User Authenticate(string login, string password)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();

            string sql = "SELECT * FROM \"user\" WHERE login = @login AND password = @password";

            using var command = new NpgsqlCommand(sql, connection);
            command.Parameters.AddWithValue("@login", login);
            command.Parameters.AddWithValue("@password", password);

            using var reader = command.ExecuteReader();
            if (reader.Read())
            {
                return new User
                {
                    Id = (int)reader["id"],
                    FirstName = reader["first_name"].ToString(),
                    LastName = reader["last_name"].ToString(),
                    Login = reader["login"].ToString(),
                    Password = reader["password"].ToString(),
                    RoleId = (int)reader["role_id"],
                    PhoneNumber = reader["phone_number"]?.ToString(),
                    Email = reader["email"].ToString()
                };
            }

            return null;
        }
        // Присваивание роли пользователю
        public void AssignRoleToUser(int userId, int roleId)
        {
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = "UPDATE \"user\" SET role_id = @RoleId WHERE id = @UserId";
                using (var command = new NpgsqlCommand(sql, connection))
                {
                    command.Parameters.AddWithValue("@RoleId", roleId);
                    command.Parameters.AddWithValue("@UserId", userId);
                    int rowsAffected = command.ExecuteNonQuery();

                    if (rowsAffected == 0)
                    {
                        Console.WriteLine("Пользователь не найден.");
                    }
                    else
                    {
                        Console.WriteLine("Роль успешно присвоена пользователю.");
                    }
                }
            }
        }
    }
}
