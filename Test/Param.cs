using System;
using System.Collections.Generic;
using System.ComponentModel.Composition;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Test
{
	[Export(typeof(Param))]
	[PartCreationPolicy(CreationPolicy.NonShared)]
	class Param
	{
		public int A { get; set; }
	}
}
