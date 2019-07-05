using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UPS.CSharp
{
	[MetadataAttribute]
	[AttributeUsage(AttributeTargets.Class, AllowMultiple = false, Inherited = false)]
	public class PluginAttribute : Attribute, IPluginMetaData
	{
		public PluginAttribute(string name)
		{
			Name = name;
		}

		public string Name { get; private set; }
	}
}
