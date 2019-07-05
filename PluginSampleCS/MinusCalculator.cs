using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UPS.CSharp;

namespace PluginSampleCS
{
	[Export(typeof(IPlugin))]
	[Plugin(nameof(MinusCalculator))]
	class MinusCalculator : IPlugin
	{
		public MinusCalculator()
		{
			Debug.WriteLine("MinusCalculator is created");
		}

		public string Invoke(string param)
		{
			var parameter = JsonConvert.DeserializeObject<Parameter>(param);
			var result = parameter.a - parameter.b;
			return JsonConvert.SerializeObject(result);
		}

		public string Name()
		{
			return nameof(MinusCalculator);
		}

		public void Set(string param)
		{
			throw new NotImplementedException();
		}

		public void Unset(string param)
		{
			throw new NotImplementedException();
		}
	}
}
