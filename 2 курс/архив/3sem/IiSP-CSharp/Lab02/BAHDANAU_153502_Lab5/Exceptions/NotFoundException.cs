using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BAHDANAU_153502_Lab5.Exceptions
{
    public class ObjectNotFoundException
        : ArgumentException
    {
        public ObjectNotFoundException(string message)
            : base(message)
        {}

        public ObjectNotFoundException()
            : base()
        { }
    }
}
