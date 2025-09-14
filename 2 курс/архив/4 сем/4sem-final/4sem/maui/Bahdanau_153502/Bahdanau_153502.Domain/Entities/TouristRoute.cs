namespace Bahdanau_153502.Domain.Entities
{
    public class TouristRoute : Entity
    {
        public string? Title { get; set; }

        public double DistanceInKm { get; set; }

        public ICollection<Landmark>? Landmarks { get; set; }

    }
}
