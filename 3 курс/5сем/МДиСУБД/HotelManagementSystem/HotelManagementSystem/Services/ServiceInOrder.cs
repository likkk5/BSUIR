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
    public class ServiceInOrderService
    {
        private readonly DatabaseManager _dbManager;

        public ServiceInOrderService(DatabaseManager dbManager)
        {
            _dbManager = dbManager;
        }

        // Create: Добавление услуги в заказ
        public void AddServiceToOrder(ServiceInOrder serviceInOrder)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand(
                "INSERT INTO service_in_order (service_id, order_id, employee_id, amount) " +
                "VALUES (@service_id, @order_id, @employee_id, @amount)", connection);
            command.Parameters.AddWithValue("@service_id", serviceInOrder.ServiceId);
            command.Parameters.AddWithValue("@order_id", serviceInOrder.OrderId);
            command.Parameters.AddWithValue("@employee_id", serviceInOrder.EmployeeId);
            command.Parameters.AddWithValue("@amount", serviceInOrder.Amount);
            command.ExecuteNonQuery();
        }

        // Read: Получить все услуги в заказах
        public List<ServiceInOrder> GetAllServiceInOrders()
        {
            var servicesInOrders = new List<ServiceInOrder>();
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand("SELECT * FROM service_in_order", connection);
            using var reader = command.ExecuteReader();
            while (reader.Read())
            {
                servicesInOrders.Add(new ServiceInOrder
                {
                    Id = reader.GetInt32(0),
                    ServiceId = reader.GetInt32(1),
                    OrderId = reader.GetInt32(2),
                    EmployeeId = reader.GetInt32(3),
                    Amount = reader.GetInt32(4)
                });
            }
            return servicesInOrders;
        }

        // Read: Получить услуги по ID заказа
        public List<ServiceInOrder> GetServicesByOrderId(int orderId)
        {
            var servicesInOrders = new List<ServiceInOrder>();
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand("SELECT * FROM service_in_order WHERE order_id = @order_id", connection);
            command.Parameters.AddWithValue("@order_id", orderId);
            using var reader = command.ExecuteReader();
            while (reader.Read())
            {
                servicesInOrders.Add(new ServiceInOrder
                {
                    Id = reader.GetInt32(0),
                    ServiceId = reader.GetInt32(1),
                    OrderId = reader.GetInt32(2),
                    EmployeeId = reader.GetInt32(3),
                    Amount = reader.GetInt32(4)
                });
            }
            return servicesInOrders;
        }

        // Update: Обновить данные услуги в заказе
        public void UpdateServiceInOrder(ServiceInOrder serviceInOrder)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand(
                "UPDATE service_in_order SET service_id = @service_id, order_id = @order_id, " +
                "employee_id = @employee_id, amount = @amount WHERE id = @id", connection);
            command.Parameters.AddWithValue("@id", serviceInOrder.Id);
            command.Parameters.AddWithValue("@service_id", serviceInOrder.ServiceId);
            command.Parameters.AddWithValue("@order_id", serviceInOrder.OrderId);
            command.Parameters.AddWithValue("@employee_id", serviceInOrder.EmployeeId);
            command.Parameters.AddWithValue("@amount", serviceInOrder.Amount);
            command.ExecuteNonQuery();
        }

        // Delete: Удалить услугу из заказа
        public void DeleteServiceInOrder(int id)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand("DELETE FROM service_in_order WHERE id = @id", connection);
            command.Parameters.AddWithValue("@id", id);
            command.ExecuteNonQuery();
        }
    }
}
