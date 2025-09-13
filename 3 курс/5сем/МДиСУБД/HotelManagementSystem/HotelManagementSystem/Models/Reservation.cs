using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HotelManagementSystem.Models
{
    public class Reservation
    {
        [Key]
        public int Id { get; set; }

        [Required]
        public DateTime ReservationDate { get; set; }

        [Required]
        public DateTime CheckInDate { get; set; }

        [Required]
        public DateTime CheckOutDate { get; set; }

        [Required]
        [MaxLength(50)]
        public string ReservationStatus { get; set; }

        [Required]
        [ForeignKey("Room")]
        public string RoomNumber { get; set; }
        public virtual Room Room { get; set; }

        [Required]
        [ForeignKey("Guest")]
        public int GuestId { get; set; }
        public virtual Guest Guest { get; set; }

        [Required]
        [Range(0, double.MaxValue)]
        public decimal Cost { get; set; }
    }
}
