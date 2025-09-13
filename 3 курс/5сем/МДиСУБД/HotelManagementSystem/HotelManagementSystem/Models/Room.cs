using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HotelManagementSystem.Models
{
    public class Room
    {
        [Key]
        public int Id { get; set; }

        [Required]
        [MaxLength(10)]
        public string RoomNumber { get; set; }

        [Required]
        [MaxLength(50)]
        public string RoomType { get; set; }

        [Required]
        [Range(0, double.MaxValue)]
        public decimal CostForNight { get; set; }

        [Required]
        [MaxLength(50)]
        public string RoomStatus { get; set; }

        public byte[] Photo { get; set; }
    }
}
