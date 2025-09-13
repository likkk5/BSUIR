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
    public class PromocodeService
    {
        private readonly DatabaseManager _dbManager;

        public PromocodeService(DatabaseManager dbManager)
        {
            _dbManager = dbManager;
        }

        public List<Promocode> GetAllPromocodes()
        {
            var promocodes = new List<Promocode>();
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = "SELECT * FROM promocode";
                using (var command = new NpgsqlCommand(sql, connection))
                using (var reader = command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        promocodes.Add(new Promocode
                        {
                            Id = (int)reader["id"],
                            Code = reader["code"].ToString(),
                            PromocodeStatus = (bool)reader["promocode_status"],
                            SaleType = reader["sale_type"].ToString(),
                            SaleAmount = (decimal)reader["sale_amount"],
                            PromocodeStartDate = (DateTime)reader["promocode_start_date"],
                            PromocodeExpirationDate = (DateTime)reader["promocode_expiration_date"],
                            PromocodeDateOfUse = reader["promocode_date_of_use"] as DateTime?
                        });
                    }
                }
            }
            return promocodes;
        }

        public void AddPromocode(Promocode promocode)
        {
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = "INSERT INTO promocode (code, promocode_status, sale_type, sale_amount, promocode_start_date, promocode_expiration_date) VALUES (@Code, @Status, @SaleType, @SaleAmount, @StartDate, @ExpirationDate)";
                using (var command = new NpgsqlCommand(sql, connection))
                {
                    command.Parameters.AddWithValue("@Code", promocode.Code);
                    command.Parameters.AddWithValue("@Status", promocode.PromocodeStatus);
                    command.Parameters.AddWithValue("@SaleType", promocode.SaleType);
                    command.Parameters.AddWithValue("@SaleAmount", promocode.SaleAmount);
                    command.Parameters.AddWithValue("@StartDate", promocode.PromocodeStartDate);
                    command.Parameters.AddWithValue("@ExpirationDate", promocode.PromocodeExpirationDate);
                    command.ExecuteNonQuery();
                }
            }
        }
    }
}
