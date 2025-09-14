namespace Bahdanau_153502.Domain.Entities
{
    public class Landmark : Entity

    {
        public string? City { get; set; }

        public string? Description { get; set; }

        public decimal? TicketPrice { get; set; }

        public int TouristRouteId { get; set; }

        public TouristRoute? TouristRoute { get; set; }
    }
}
