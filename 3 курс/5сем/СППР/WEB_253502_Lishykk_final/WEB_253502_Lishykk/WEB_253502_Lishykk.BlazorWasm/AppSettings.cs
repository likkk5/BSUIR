namespace WEB_253502_Lishykk.BlazorWasm
{
    public class ApiSettings
    {
        public string ApiBaseUrl { get; set; }
        public string PageSize { get; set; }
    }

    public class AppSettings
    {
        public ApiSettings ApiSettings { get; set; }
    }
}
