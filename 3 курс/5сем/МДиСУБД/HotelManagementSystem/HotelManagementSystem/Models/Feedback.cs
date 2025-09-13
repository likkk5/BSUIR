using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HotelManagementSystem.Models
{
    public class Feedback
    {
        [Key]
        public int Id { get; set; }

        [Required]
        [ForeignKey("Guest")]
        public int GuestId { get; set; }
        public virtual Guest Guest { get; set; }

        [Required]
        public DateTime FeedbackDateTime { get; set; }

        public string FeedbackText { get; set; }

        [Required]
        [Range(1, 5)]
        public int Rating { get; set; }
    }
}
