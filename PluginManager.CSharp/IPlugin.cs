using System;
using System.Collections.Generic;
using System.Text;

namespace UPS.CSharp
{
    public interface IPlugin
    {
        string Name();
        /// <summary>
        /// set global parameters, will throw exception if the param is not valid
        /// </summary>
        /// <param name="param">a json string</param>
        void Set(string param);
        void Unset(string param);
        string Invoke(string param);
    }
}
