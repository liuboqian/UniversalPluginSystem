using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UPS.CSharp;
using UPS.CSharp.Tests;

namespace UPS.CSharp.Tests
{
	[TestClass()]
	public class PluginManagerCSharpAllPlatformTests
	{
		private PluginManagerCSharp _manager;

		[TestInitialize]
		public void Init()
		{
			_manager = new PluginManagerCSharp();
			_manager.ComposeAll();
		}

		[TestMethod()]
		public void PluginManagerCSharpTest()
		{
			_manager = new PluginManagerCSharp();
		}

		[TestMethod()]
		public void AllPartsTest()
		{
			Assert.AreEqual(_manager.AllParts.Count, 1);
			Assert.IsTrue(_manager.AllParts.Contains(Path.GetDirectoryName(_manager.GetType().Assembly.Location)));
			_manager.Parts.Clear();
			Assert.AreEqual(_manager.AllParts.Count, 1);
		}

		[TestMethod()]
		public void CSPluginsTest()
		{
			foreach (var plugin in _manager.AllPlugins)
			{
				Assert.IsInstanceOfType(plugin, typeof(IPlugin));
			}
		}

		[TestMethod()]
		public void PluginTest()
		{
			Assert.IsTrue(_manager.AllPluginNames.Length >= _manager.Plugins.Length);
			Assert.AreEqual(_manager.AllPluginNames.Count(), 3);

			foreach (var name in _manager.AllPluginNames)
			{
				Assert.AreEqual(_manager.GetPlugin(name).Name(), name);
			}
		}
	}
}
