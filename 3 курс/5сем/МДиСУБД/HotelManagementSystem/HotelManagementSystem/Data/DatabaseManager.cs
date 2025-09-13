using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Npgsql;

namespace HotelManagementSystem.Data
{
    public class DatabaseManager
    {
        private readonly string _connectionString;

        public DatabaseManager(string host, string database, string username, string password)
        {
            // Формируем строку подключения
            _connectionString = $"Host={host};Database={database};Username={username};Password={password}";
        }

        public NpgsqlConnection GetConnection()
        {
            return new NpgsqlConnection(_connectionString); // Возвращаем подключение
        }
    }
}
