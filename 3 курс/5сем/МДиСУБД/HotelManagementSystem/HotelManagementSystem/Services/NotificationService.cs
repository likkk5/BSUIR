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
    public class NotificationService
    {
        private readonly DatabaseManager _dbManager;

        public NotificationService(DatabaseManager dbManager)
        {
            _dbManager = dbManager;
        }

        // Create: Создать уведомление
        public void CreateNotification(Notification notification)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();

            var command = new NpgsqlCommand(
                "INSERT INTO notification (notification_datetime, notification_text, order_id) " +
                "VALUES (@notification_datetime, @notification_text, @order_id)", connection);

            command.Parameters.AddWithValue("@notification_datetime", notification.NotificationDateTime);
            command.Parameters.AddWithValue("@notification_text", notification.NotificationText);
            command.Parameters.AddWithValue("@order_id", notification.OrderId);

            command.ExecuteNonQuery();
        }


        // Read: Получить все уведомления
        public List<Notification> GetAllNotifications()
        {
            var notifications = new List<Notification>();
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand("SELECT * FROM notification", connection);
            using var reader = command.ExecuteReader();
            while (reader.Read())
            {
                notifications.Add(new Notification
                {
                    Id = reader.GetInt32(0),
                    NotificationDateTime = reader.GetDateTime(1),
                    NotificationText = reader.GetString(2),
                    OrderId = reader.GetInt32(3),
                });
            }
            return notifications;
        }

        // Read: Получить уведомление по ID
        public Notification GetNotificationById(int id)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand("SELECT * FROM notification WHERE id = @id", connection);
            command.Parameters.AddWithValue("@id", id);
            using var reader = command.ExecuteReader();
            if (reader.Read())
            {
                return new Notification
                {
                    Id = reader.GetInt32(0),
                    NotificationDateTime = reader.GetDateTime(1),
                    NotificationText = reader.GetString(2),
                    OrderId = reader.GetInt32(3),
                };
            }
            return null;
        }

        // Update: Обновить уведомление
        public void UpdateNotification(Notification notification)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand(
                "UPDATE notification SET notification_datetime = @notification_datetime, notification_text = @notification_text, order_id = @order_id " +
                "WHERE id = @id", connection); 
            command.Parameters.AddWithValue("@id", notification.Id);
            command.Parameters.AddWithValue("@notification_datetime", notification.NotificationDateTime);
            command.Parameters.AddWithValue("@notification_text", notification.NotificationText);
            command.Parameters.AddWithValue("@order_id", notification.OrderId);
            command.ExecuteNonQuery();
        }


        // Delete: Удалить уведомление
        public void DeleteNotification(int id)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand("DELETE FROM notification WHERE id = @id", connection);
            command.Parameters.AddWithValue("@id", id);
            command.ExecuteNonQuery();
        }
        public List<Notification> GetOrderNotifications(int userId)
        {
            var notifications = new List<Notification>();
            using var connection = _dbManager.GetConnection();
            connection.Open();

            var command = new NpgsqlCommand(@"
            SELECT n.id, n.notification_datetime, n.notification_text, n.order_id, o.order_status, o.reservation_id, o.cost
            FROM notification n
            JOIN ""order"" o ON n.order_id = o.id
            WHERE o.employee_id = @userId", connection);  // Фильтруем по ID пользователя 

            command.Parameters.AddWithValue("@userId", userId);

            using var reader = command.ExecuteReader();
            while (reader.Read())
            {
                var notification = new Notification
                {
                    Id = reader.GetInt32(0),
                    NotificationDateTime = reader.GetDateTime(1),
                    NotificationText = reader.GetString(2),
                    OrderId = reader.GetInt32(3),
                    Order = new Order
                    {
                        Id = reader.GetInt32(3),
                        OrderStatus = reader.GetString(4),
                        ReservationId = reader.GetInt32(5), // Получаем ReservationId из заказа
                        Cost = reader.IsDBNull(6) ? 0 : reader.GetDecimal(6) // Обработка возможного NULL для стоимости
                    }
                };
                notifications.Add(notification);
            }

            return notifications;
        }

    }
}
