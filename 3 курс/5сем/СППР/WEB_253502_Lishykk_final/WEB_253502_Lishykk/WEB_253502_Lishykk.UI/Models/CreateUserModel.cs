namespace WEB_253502_Lishykk.UI.Models
{
    class CreateUserModel
    {
        public Dictionary<string, string> Attributes { get; set; } = new();
        public string Username { get; set; }
        public string Email { get; set; }
        public bool Enabled { get; set; } = true;
        public bool EmailVerified { get; set; } = true;
        public List<UserCredentials> Credentials { get; set; } = new();
    }
    class UserCredentials
    {
        public string Type { get; set; } = "password";
        public bool Temporary { get; set; } = false;
        public string Value { get; set; }
    }
}
