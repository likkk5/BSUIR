using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HotelManagementSystem.Models
{
    public class ReservationPromocodes
    {
        [Key]
        public int Id { get; set; }

        [ForeignKey("Promocode")]
        public int? PromocodeId { get; set; }

        [Required]
        [ForeignKey("Reservation")]
        public int ReservationId { get; set; }

        [Range(0, int.MaxValue)]
        public int Quantity { get; set; }
    }
}
