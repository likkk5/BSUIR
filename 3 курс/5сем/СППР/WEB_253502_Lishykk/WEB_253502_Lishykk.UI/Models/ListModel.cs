namespace WEB_253502_Lishykk.UI.Models
{
    public class ListModel<T>
    {
        public IEnumerable<T> Items { get; set; }
        public int CurrentPage { get; set; }
        public int TotalPages { get; set; }
    }
}
