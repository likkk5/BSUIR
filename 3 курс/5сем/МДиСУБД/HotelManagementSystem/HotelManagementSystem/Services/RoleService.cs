using System.Collections.Generic;
using HotelManagementSystem.Data;
using HotelManagementSystem.Models;
using Npgsql;

namespace HotelManagementSystem.Services
{
    public class RoleService
    {
        private readonly DatabaseManager _dbManager;

        public RoleService(DatabaseManager dbManager)
        {
            _dbManager = dbManager;
        }

        public List<Role> GetAllRoles()
        {
            var roles = new List<Role>();
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = "SELECT * FROM roles";
                using (var command = new NpgsqlCommand(sql, connection))
                using (var reader = command.ExecuteReader())
                {
                    while (reader.Read())
                    {
                        roles.Add(new Role
                        {
                            Id = (int)reader["id"],
                            RoleName = reader["role_name"].ToString()
                        });
                    }
                }
            }
            return roles;
        }

        public Role GetRoleById(int id)
        {
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = "SELECT * FROM roles WHERE id = @Id";
                using (var command = new NpgsqlCommand(sql, connection))
                {
                    command.Parameters.AddWithValue("@Id", id);
                    using (var reader = command.ExecuteReader())
                    {
                        if (reader.Read())
                        {
                            return new Role
                            {
                                Id = (int)reader["id"],
                                RoleName = reader["role_name"].ToString()
                            };
                        }
                    }
                }
            }
            return null;
        }

        public void AddRole(Role role)
        {
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = "INSERT INTO roles (role_name) VALUES (@RoleName)";
                using (var command = new NpgsqlCommand(sql, connection))
                {
                    command.Parameters.AddWithValue("@RoleName", role.RoleName);
                    command.ExecuteNonQuery();
                }
            }
        }

        public void UpdateRole(Role role)
        {
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = "UPDATE roles SET role_name = @RoleName WHERE id = @Id";
                using (var command = new NpgsqlCommand(sql, connection))
                {
                    command.Parameters.AddWithValue("@RoleName", role.RoleName);
                    command.Parameters.AddWithValue("@Id", role.Id);
                    command.ExecuteNonQuery();
                }
            }
        }

        public void DeleteRole(int id)
        {
            using (var connection = _dbManager.GetConnection())
            {
                connection.Open();
                string sql = "DELETE FROM roles WHERE id = @Id";
                using (var command = new NpgsqlCommand(sql, connection))
                {
                    command.Parameters.AddWithValue("@Id", id);
                    command.ExecuteNonQuery();
                }
            }
        }

    }
}
