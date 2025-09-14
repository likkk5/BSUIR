using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using BAHDANAU_153502_Lab5.Collections;

namespace BAHDANAU_153502_Lab5.Entities
{
    public class Journal
    {
        private MyCustomCollection<string> logs;
        
        public Journal()
        {
            logs = new MyCustomCollection<string>();
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
