﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task01.Interfaces
{
    interface IFileService<T>
    {
        public IEnumerable<T> ReadFile(string fileName);
        public void SaveData(IEnumerable<T> data, string fileName);
    }
}
