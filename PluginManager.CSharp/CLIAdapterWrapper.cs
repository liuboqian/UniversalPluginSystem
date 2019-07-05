using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace UPS.CSharp
{
	static class CLIAdapterWrapper
	{
		[DllImport("PluginManager.CLI.dll", EntryPoint = "pluginManagerType", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
		public static extern IntPtr PluginManagerType();

		[DllImport("PluginManager.CLI.dll", EntryPoint = "createPluginManager")]
		public static extern IntPtr CreateCLIAdapater(bool allplatform);

		[DllImport("PluginManager.CLI.dll", EntryPoint = "deletePluginManager")]
		public static extern void DeleteCLIAdapater(IntPtr manager);

		[DllImport("PluginManager.CLI.dll", EntryPoint = "injectManager", CallingConvention = CallingConvention.Cdecl)]
		public static extern void InjectManager(IntPtr wrapper, IntPtr manager);

	}
}
