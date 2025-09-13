using System;
using System.Collections.Generic;
using HotelManagementSystem.Data;
using HotelManagementSystem.Models;
using Npgsql;

namespace HotelManagementSystem.Services
{
    public class OrderService
    {
        private readonly DatabaseManager _dbManager;

        public OrderService(DatabaseManager dbManager)
        {
            _dbManager = dbManager;
        }

        // Create: Создать заказ
        //public void CreateOrder(Order order)
        //{
        //    using var connection = _dbManager.GetConnection();
        //    connection.Open();
        //    var command = new NpgsqlCommand(
        //        "INSERT INTO \"order\" (order_datetime, reservation_id, order_status, notification_id, employee_id, cost) " +
        //        "VALUES (@order_datetime, @reservation_id, @order_status, @notification_id, @employee_id, @cost)", connection);
        //    command.Parameters.AddWithValue("@order_datetime", order.OrderDateTime);
        //    command.Parameters.AddWithValue("@reservation_id", order.ReservationId);
        //    command.Parameters.AddWithValue("@order_status", order.OrderStatus);
        //    command.Parameters.AddWithValue("@notification_id", order.NotificationId ?? (object)DBNull.Value);
        //    command.Parameters.AddWithValue("@employee_id", order.EmployeeId);
        //    command.Parameters.AddWithValue("@cost", order.Cost);
        //    command.ExecuteNonQuery();
        //}
        public int CreateOrder(Order order)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand(
                "INSERT INTO \"order\" (order_datetime, reservation_id, order_status, notification_id, employee_id, cost) " +
                "VALUES (@order_datetime, @reservation_id, @order_status, @notification_id, @employee_id, @cost) " +
                "RETURNING id", connection); // Добавляем RETURNING id для получения сгенерированного ID
            command.Parameters.AddWithValue("@order_datetime", order.OrderDateTime);
            command.Parameters.AddWithValue("@reservation_id", order.ReservationId);
            command.Parameters.AddWithValue("@order_status", order.OrderStatus);
            command.Parameters.AddWithValue("@notification_id", order.NotificationId ?? (object)DBNull.Value);
            command.Parameters.AddWithValue("@employee_id", order.EmployeeId);
            command.Parameters.AddWithValue("@cost", order.Cost);

            // Получаем ID нового заказа
            return Convert.ToInt32(command.ExecuteScalar());
        }

        // Read: Получить все заказы
        public List<Order> GetAllOrders()
        {
            var orders = new List<Order>();
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand("SELECT * FROM \"order\"", connection);
            using var reader = command.ExecuteReader();
            while (reader.Read())
            {
                orders.Add(new Order
                {
                    Id = reader.GetInt32(0),
                    OrderDateTime = reader.GetDateTime(1),
                    ReservationId = reader.GetInt32(2),
                    OrderStatus = reader.GetString(3),
                    NotificationId = reader.IsDBNull(4) ? null : reader.GetInt32(4),
                    EmployeeId = reader.GetInt32(5),
                    Cost = reader.GetDecimal(6)
                });
            }
            return orders;
        }

        // Read: Получить заказ по ID
        public Order GetOrderById(int id)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand("SELECT * FROM \"order\" WHERE id = @id", connection);
            command.Parameters.AddWithValue("@id", id);
            using var reader = command.ExecuteReader();
            if (reader.Read())
            {
                return new Order
                {
                    Id = reader.GetInt32(0),
                    OrderDateTime = reader.GetDateTime(1),
                    ReservationId = reader.GetInt32(2),
                    OrderStatus = reader.GetString(3),
                    NotificationId = reader.IsDBNull(4) ? null : reader.GetInt32(4),
                    EmployeeId = reader.GetInt32(5),
                    Cost = reader.GetDecimal(6)
                };
            }
            return null;
        }

        // Update: Обновить заказ
        public void UpdateOrder(Order order)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand(
                "UPDATE \"order\" SET order_datetime = @order_datetime, reservation_id = @reservation_id, " +
                "order_status = @order_status, notification_id = @notification_id, employee_id = @employee_id, cost = @cost " +
                "WHERE id = @id", connection);
            command.Parameters.AddWithValue("@id", order.Id);
            command.Parameters.AddWithValue("@order_datetime", order.OrderDateTime);
            command.Parameters.AddWithValue("@reservation_id", order.ReservationId);
            command.Parameters.AddWithValue("@order_status", order.OrderStatus);
            command.Parameters.AddWithValue("@notification_id", order.NotificationId ?? (object)DBNull.Value);
            command.Parameters.AddWithValue("@employee_id", order.EmployeeId);
            command.Parameters.AddWithValue("@cost", order.Cost);
            command.ExecuteNonQuery();
        }

        // Delete: Удалить заказ
        public void DeleteOrder(int id)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand("DELETE FROM \"order\" WHERE id = @id", connection);
            command.Parameters.AddWithValue("@id", id);
            command.ExecuteNonQuery();
        }
        // Получить заказ по ID брони
        //public Order GetOrderByReservationId(int reservationId)
        //{
        //    using var connection = _dbManager.GetConnection();
        //    connection.Open();
        //    var command = new NpgsqlCommand("SELECT * FROM \"order\" WHERE reservation_id = @reservation_id", connection);
        //    command.Parameters.AddWithValue("@reservation_id", reservationId);
        //    using var reader = command.ExecuteReader();
        //    if (reader.Read())
        //    {
        //        return new Order
        //        {
        //            Id = reader.GetInt32(0),
        //            OrderDateTime = reader.GetDateTime(1),
        //            ReservationId = reader.GetInt32(2),
        //            OrderStatus = reader.GetString(3),
        //            NotificationId = reader.IsDBNull(4) ? null : reader.GetInt32(4),
        //            EmployeeId = reader.GetInt32(5),
        //            Cost = reader.GetDecimal(6)
        //        };
        //    }
        //    return null; // Если заказ не найден
        //}
        public Order GetOrderByReservationId(int reservationId)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();

            var command = new NpgsqlCommand(@"
        SELECT * 
        FROM ""order"" 
        WHERE reservation_id = @reservation_id
        ORDER BY id DESC  -- Сортируем по ID в порядке убывания, чтобы последний заказ был первым
        LIMIT 1", connection);  // Берем только одну запись

            command.Parameters.AddWithValue("@reservation_id", reservationId);

            using var reader = command.ExecuteReader();
            if (reader.Read())
            {
                return new Order
                {
                    Id = reader.GetInt32(0),
                    OrderDateTime = reader.GetDateTime(1),
                    ReservationId = reader.GetInt32(2),
                    OrderStatus = reader.GetString(3),
                    NotificationId = reader.IsDBNull(4) ? null : reader.GetInt32(4),
                    EmployeeId = reader.GetInt32(5),
                    Cost = reader.GetDecimal(6)
                };
            }

            return null; 
        }

        // Пересчитать стоимость заказа
        public void RecalculateOrderCost(int orderId)
        {
            try
            {
                //вызов процедуры пересчёта стоимости заказа
                string query = $"CALL recalculate_order_cost(@orderId);";

                using var connection = _dbManager.GetConnection();
                connection.Open();

                using (var command = new NpgsqlCommand(query, connection))
                {

                    command.Parameters.AddWithValue("@orderId", orderId);
                    command.ExecuteNonQuery();
                }

                Console.WriteLine("Стоимость заказа пересчитана.");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Ошибка при пересчете стоимости заказа: {ex.Message}");
            }
        }

    }
}
