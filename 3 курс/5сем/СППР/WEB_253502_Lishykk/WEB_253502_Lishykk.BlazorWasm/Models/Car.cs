namespace WEB_253502_Lishykk.BlazorWasm.Models
{
    public class Car
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public string Description { get; set; }
        public int? CategoryId { get; set; }
        public decimal Price { get; set; }
        public string? ImagePath { get; set; }
        public string? ImageMimeType { get; set; }
        //public Category? Category { get; set; }
    }

}
