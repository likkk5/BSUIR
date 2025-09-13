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
    public class FeedbackService
    {
        private readonly DatabaseManager _dbManager;

        public FeedbackService(DatabaseManager dbManager)
        {
            _dbManager = dbManager;
        }

        // Create
        public void AddFeedback(Feedback feedback)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand(
                "INSERT INTO feedback (guest_id, feedback_datetime, feedback_text, rating) " +
                "VALUES (@guest_id, @feedback_datetime, @feedback_text, @rating)", connection);
            command.Parameters.AddWithValue("@guest_id", feedback.GuestId);
            command.Parameters.AddWithValue("@feedback_datetime", feedback.FeedbackDateTime);
            command.Parameters.AddWithValue("@feedback_text", feedback.FeedbackText ?? (object)DBNull.Value);
            command.Parameters.AddWithValue("@rating", feedback.Rating);
            command.ExecuteNonQuery();
        }

        // Read (Get All)
        public List<Feedback> GetAllFeedbacks()
        {
            var feedbacks = new List<Feedback>();
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand("SELECT * FROM feedback", connection);
            using var reader = command.ExecuteReader();
            while (reader.Read())
            {
                feedbacks.Add(new Feedback
                {
                    Id = reader.GetInt32(0),
                    GuestId = reader.GetInt32(1),
                    FeedbackDateTime = reader.GetDateTime(2),
                    FeedbackText = reader.IsDBNull(3) ? null : reader.GetString(3),
                    Rating = reader.GetInt32(4)
                });
            }
            return feedbacks;
        }

        // Read (Get by ID)
        public Feedback GetFeedbackById(int id)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand("SELECT * FROM feedback WHERE id = @id", connection);
            command.Parameters.AddWithValue("@id", id);
            using var reader = command.ExecuteReader();
            if (reader.Read())
            {
                return new Feedback
                {
                    Id = reader.GetInt32(0),
                    GuestId = reader.GetInt32(1),
                    FeedbackDateTime = reader.GetDateTime(2),
                    FeedbackText = reader.IsDBNull(3) ? null : reader.GetString(3),
                    Rating = reader.GetInt32(4)
                };
            }
            return null;
        }

        // Update
        public void UpdateFeedback(Feedback feedback)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand(
                "UPDATE feedback SET feedback_datetime = @feedback_datetime, feedback_text = @feedback_text, rating = @rating " +
                "WHERE id = @id", connection);
            command.Parameters.AddWithValue("@id", feedback.Id);
            command.Parameters.AddWithValue("@feedback_datetime", feedback.FeedbackDateTime);
            command.Parameters.AddWithValue("@feedback_text", feedback.FeedbackText ?? (object)DBNull.Value);
            command.Parameters.AddWithValue("@rating", feedback.Rating);
            command.ExecuteNonQuery();
        }

        // Delete
        public void DeleteFeedback(int id)
        {
            using var connection = _dbManager.GetConnection();
            connection.Open();
            var command = new NpgsqlCommand("DELETE FROM feedback WHERE id = @id", connection);
            command.Parameters.AddWithValue("@id", id);
            command.ExecuteNonQuery();
        }
    }
}
