using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HotelManagementSystem.Models
{
    public class Promocode
    {
        [Key]
        public int Id { get; set; }

        [Required]
        [MaxLength(50)]
        public string Code { get; set; }

        [Required]
        public bool PromocodeStatus { get; set; }

        [Required]
        [MaxLength(20)]
        public string SaleType { get; set; }

        [Required]
        [Range(0, double.MaxValue)]
        public decimal SaleAmount { get; set; }

        [Required]
        public DateTime PromocodeStartDate { get; set; }

        [Required]
        public DateTime PromocodeExpirationDate { get; set; }

        public DateTime? PromocodeDateOfUse { get; set; }
    }
}
