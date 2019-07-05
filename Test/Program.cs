using System;
using System.Collections.Generic;
using System.ComponentModel.Composition.Hosting;
using System.ComponentModel.Composition;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Runtime.InteropServices;
using UPS.CSharp;

namespace Test
{
	class Program
	{
		[DllImport("PluginManager.CLI.dll", EntryPoint = "createPluginManager")]
		private static extern IntPtr CreateCLIAdapater(bool allplatform);

		[DllImport("PluginManager.CLI.dll", EntryPoint = "deletePluginManager")]
		private static extern void DeleteCLIAdapater(IntPtr manager);

		static void Main(string[] args)
		{
			//PluginManagerCSharp manager = new PluginManagerCSharp();
			//Console.WriteLine(manager.Parts.Count);

			//try
			//{
			//	PluginManagerCSharp manager = new PluginManagerCSharp();
			//	Console.WriteLine(manager.Parts.Count);
			//}
			//catch (ReflectionTypeLoadException ex)
			//{
			//	StringBuilder sb = new StringBuilder();
			//	foreach (Exception exSub in ex.LoaderExceptions)
			//	{
			//		sb.AppendLine(exSub.Message);
			//		FileNotFoundException exFileNotFound = exSub as FileNotFoundException;
			//		if (exFileNotFound != null)
			//		{
			//			if (!string.IsNullOrEmpty(exFileNotFound.FusionLog))
			//			{
			//				sb.AppendLine("Fusion Log:");
			//				sb.AppendLine(exFileNotFound.FusionLog);
			//			}
			//		}
			//		sb.AppendLine();
			//	}
			//	Console.WriteLine(sb.ToString());
			//	//Display or log the error based on your application.
			//}

			//AssemblyCatalog catalog = new AssemblyCatalog(typeof(Program).Assembly);
			//CompositionContainer container = new CompositionContainer(catalog);
			//var a = container.GetExportedValue<Param>();
			//a.A = 3;
			//var b = container.GetExportedValue<Param>();

			//Debug.Assert(a != b);

			PluginManagerCSharp manager = new PluginManagerCSharp(true);
			manager.ComposeAll();
			var names = manager.AllPluginNames;
			foreach (var name in names)
			{
				var plugin = manager.GetPlugin(name);
				Console.WriteLine(plugin.Name());
			}

			var plugin2 = manager.GetPlugin("a");

			//Process.Start(new ProcessStartInfo("testCpp.exe"));


			Console.ReadKey();
		}
	}
}
