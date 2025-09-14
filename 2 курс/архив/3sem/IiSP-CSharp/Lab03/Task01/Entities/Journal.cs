namespace BAHDANAU_153502_Lab5.Entities
{
    public class Journal
    {
        private List<string> logs;
        public Journal()
        {
            logs = new List<string>();
        }

        public void Log(string log)
        {
            logs.Add(log);
        }

        public string GetLogs()
        {
            string res = "";
            foreach (var item in logs)
            {
                res += item + "\n";
            }
            return res;
        }
    }
}
