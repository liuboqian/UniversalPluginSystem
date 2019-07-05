using Microsoft.VisualStudio.TestTools.UnitTesting;
using UPS.CSharp;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using Newtonsoft.Json;

namespace UPS.CSharp.Tests
{
	[TestClass()]
	public class PluginManagerCSharpTests
	{
		private PluginManagerCSharp _manager;

		[TestInitialize]
		public void Init()
		{
			_manager = new PluginManagerCSharp(false);
			_manager.Compose();
		}

		[TestMethod()]
		public void PluginManagerCSharpTest()
		{
			_manager = new PluginManagerCSharp(false);
		}

		[TestMethod()]
		public void PartsTest()
		{
			Assert.AreEqual(_manager.Parts.Count, 1);
			Assert.AreEqual(_manager.Parts[0], Path.GetDirectoryName(_manager.GetType().Assembly.Location));
			_manager.Parts.Clear();
			Assert.AreEqual(_manager.Parts.Count, 0);
			_manager.Compose();
			Assert.AreEqual(_manager.PluginNames.Count(), 0);

			_manager.Parts.Add("test");
			Assert.AreEqual(_manager.Parts.Count, 1);
			_manager.Parts.Add("test");
			Assert.AreEqual(_manager.Parts.Count, 1);
		}

		[TestMethod()]
		public void PluginTest()
		{
			Assert.AreEqual(_manager.Plugins.Length, _manager.PluginNames.Count());
			Assert.AreEqual(_manager.PluginNames.Count(), 2);

			var plugin = _manager.GetPlugin("AddCalculator");  // CSharp plugin, add calculator
			Assert.AreEqual(plugin.Name(), "AddCalculator");
			Parameter p = new Parameter() { a = 1, b = 2 };
			var result = plugin.Invoke(JsonConvert.SerializeObject(p));
			Assert.IsTrue(Math.Abs(JsonConvert.DeserializeObject<double>(result) - 3.0) < double.Epsilon);

			plugin = _manager.GetPlugin("MinusCalculator");
			Assert.AreEqual(plugin.Name(), "MinusCalculator");
			p = new Parameter() { a = 3, b = 2 };
			result = plugin.Invoke(JsonConvert.SerializeObject(p));
			Assert.IsTrue(Math.Abs(JsonConvert.DeserializeObject<double>(result) - 1.0) < double.Epsilon);
		}

		[TestMethod]
		public void PluginReferenceTest()
		{
			var plugin1 = _manager.GetPlugin(_manager.PluginNames[0]);

			var origindir = _manager.Parts.First();
			_manager.Parts.Clear();
			_manager.Compose();

			_manager.Parts.Add(origindir);
			_manager.Compose();

			Assert.AreNotEqual(plugin1, _manager.GetPlugin(_manager.PluginNames[0]));
		}
	}
}