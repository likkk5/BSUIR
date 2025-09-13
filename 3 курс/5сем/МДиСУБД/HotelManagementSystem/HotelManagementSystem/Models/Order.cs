using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HotelManagementSystem.Models
{
    public class Order
    {
        [Key]
        public int Id { get; set; }

        [Required]
        public DateTime OrderDateTime { get; set; }

        [Required]
        [ForeignKey("Reservation")]
        public int ReservationId { get; set; }
        public virtual Reservation Reservation { get; set; }

        [Required]
        [MaxLength(50)]
        public string OrderStatus { get; set; }

        [ForeignKey("Notification")]
        public int? NotificationId { get; set; }

        [Required]
        [ForeignKey("User")]
        public int EmployeeId { get; set; }

        [Required]
        [Range(0, double.MaxValue)]
        public decimal Cost { get; set; }
    }
}
