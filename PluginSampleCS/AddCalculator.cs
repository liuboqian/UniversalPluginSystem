using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UPS.CSharp;
using Newtonsoft.Json;
using System.Diagnostics;

namespace PluginSampleCS
{
	[Export(typeof(IPlugin))]
	[Plugin(nameof(AddCalculator))]
	public class AddCalculator : IPlugin
	{
		public AddCalculator()
		{
			Debug.WriteLine("Add Calculator is created");
		}
		
		public string Invoke(string param)
		{
			var parameter = JsonConvert.DeserializeObject<Parameter>(param);
			var result = parameter.a + parameter.b;
			return JsonConvert.SerializeObject(result);
		}

		public string Name()
		{
			return nameof(AddCalculator);
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
