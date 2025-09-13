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
    public class ServiceService
    {
        private readonly DatabaseManager _dbManager;

        public ServiceService(DatabaseManager dbManager)
        {
            _dbManager = dbManager;
        }

        // Create
        public void AddService(Service service)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand(
                "INSERT INTO service (name, cost, photo) VALUES (@name, @cost, @photo)", connection);
            command.Parameters.AddWithValue("@name", service.Name);
            command.Parameters.AddWithValue("@cost", service.Cost);
            command.Parameters.AddWithValue("@photo", service.Photo ?? (object)DBNull.Value);
            command.ExecuteNonQuery();
        }

        // Read (Get All)
        public List<Service> GetAllServices()
        {
            var services = new List<Service>();
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand("SELECT * FROM service", connection);
            using var reader = command.ExecuteReader();
            while (reader.Read())
            {
                services.Add(new Service
                {
                    Id = reader.GetInt32(0),
                    Name = reader.GetString(1),
                    Cost = reader.GetDecimal(2),
                    Photo = reader.IsDBNull(3) ? null : (byte[])reader["photo"]
                });
            }
            return services;
        }

        // Read (Get by ID)
        public Service GetServiceById(int id)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand("SELECT * FROM service WHERE id = @id", connection);
            command.Parameters.AddWithValue("@id", id);
            using var reader = command.ExecuteReader();
            if (reader.Read())
            {
                return new Service
                {
                    Id = reader.GetInt32(0),
                    Name = reader.GetString(1),
                    Cost = reader.GetDecimal(2),
                    Photo = reader.IsDBNull(3) ? null : (byte[])reader["photo"]
                };
            }
            return null;
        }

        // Update
        public void UpdateService(Service service)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand(
                "UPDATE service SET name = @name, cost = @cost, photo = @photo WHERE id = @id", connection);
            command.Parameters.AddWithValue("@id", service.Id);
            command.Parameters.AddWithValue("@name", service.Name);
            command.Parameters.AddWithValue("@cost", service.Cost);
            command.Parameters.AddWithValue("@photo", service.Photo ?? (object)DBNull.Value);
            command.ExecuteNonQuery();
        }

        // Delete
        public void DeleteService(int id)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand("DELETE FROM service WHERE id = @id", connection);
            command.Parameters.AddWithValue("@id", id);
            command.ExecuteNonQuery();
        }
    }
}
