using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HotelManagementSystem.Models
{
    public class Notification
    {
        [Key]
        public int Id { get; set; }

        [Required]
        public DateTime NotificationDateTime { get; set; }

        [Required]
        public string NotificationText { get; set; }
        public int OrderId { get; set; }
        public virtual Order Order { get; set; }
    }
}
