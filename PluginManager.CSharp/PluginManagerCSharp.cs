using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Text;
using System.ComponentModel.Composition;
using System.ComponentModel.Composition.Hosting;
using System.Collections.Specialized;
using System.ComponentModel.Composition.Primitives;
using System.IO;
using System.Reflection;
using System.Linq;
using System.Runtime.InteropServices;

namespace UPS.CSharp
{
	public class PluginManagerCSharp
	{
		#region private members

		private ObservableCollection<string> _parts;
		private CompositionContainer _container;
		private AggregateCatalog _catalog;
		private bool _allplatform;

		#endregion

		#region Properties

		public IList<string> AllParts
		{
			get
			{
				List<string> result = new List<string>();
				if (AllPlatform)
					result.AddRange(InvokeFactoryMethod("getGlobalParts") as string[]);
				else
					result.AddRange(Parts);
				return result;
			}
		}
		public IList<string> Parts => _parts;

		[ImportMany(typeof(IPlugin), AllowRecomposition = true)]
		public Lazy<IPlugin, IPluginMetaData>[] Plugins { get; set; }

		public IPlugin[] AllPlugins
		{
			get
			{
				return InvokeFactoryMethod("getAllPlugins") as IPlugin[];
			}
		}

		public string[] PluginNames
		{
			get
			{
				return (from item in Plugins
								select item.Metadata.Name).ToArray();
			}
		}

		public string[] AllPluginNames
		{
			get
			{
				return InvokeFactoryMethod("getAllPluginNames") as string[];
			}
		}

		public bool AllPlatform
		{
			get => _allplatform;
			set
			{
				if (_allplatform != value)
				{
					_allplatform = value;
					if (value && Factory == null)
						CreateFactory();
					else
					{
						//Factory = null;
					}
				}
			}
		}


		// reference to PluginManagerFactoryWrapper
		public object Factory { get; set; }
		// reference to PluginManagerCSAdapter
		public IntPtr Wrapper { get; set; }

		#endregion

		public PluginManagerCSharp(bool allPlatform = true)//, UPS.CLI.PluginManagerCppAdapter managerCpp = null)
		{
			_catalog = new AggregateCatalog();
			_container = new CompositionContainer(_catalog);
			_parts = new ObservableCollection<string>();
			_parts.CollectionChanged += _parts_CollectionChanged;

			_parts.Add(Environment.CurrentDirectory);

			// cpp manager
			//_cppmanager = managerCpp;
			AllPlatform = allPlatform;
		}

		public void Compose()
		{
			_catalog.Catalogs.Clear();
			foreach (var part in AllParts)
			{
				var catalog = GetCatalogFromFileOrDirectory(part);
				if (catalog == null)
					Logger.Error($"{part} is not a file or directory");
				else
					_catalog.Catalogs.Add(catalog);
			}
			_container.ComposeParts(this);
		}

		public void ComposeAll()
		{
			if (AllPlatform && DLLExists())
			{
				InvokeFactoryMethod("composeAll");
			}
			else
				Compose();
		}

		private void CreateFactory()
		{
			if (DLLExists())
			{
				var handle = GCHandle.Alloc(this);
				var ptr = GCHandle.ToIntPtr(handle);
				if (Wrapper == IntPtr.Zero)
					Wrapper = CLIAdapterWrapper.CreateCLIAdapater(false);
				CLIAdapterWrapper.InjectManager(Wrapper, ptr);

				if (Factory == null)
					Logger.Error("Failed to create CLI Adapter");
			}
			else
			{
				Logger.Error("Can't create CLI Adapter because dll doesn't exist");
			}
		}

		private bool DLLExists()
		{
			try
			{
				var path = Path.Combine(Environment.CurrentDirectory, "PluginManager.CLI.dll");
				if (!File.Exists(path))
					return false;
				var name = Marshal.PtrToStringAnsi(CLIAdapterWrapper.PluginManagerType());
				if (name != "CSharp")
					return false;
			}
			catch (Exception e)
			{
				Logger.Error(e.Message);
				return false;
			}

			return true;
		}

		public IPlugin GetPlugin(string name)
		{
			var plugin = GetPluginInternal(name);
			if (plugin != null)
				return plugin;
			else if (AllPlatform)
				return InvokeFactoryMethod("getPlugin", name) as IPlugin;
			return null;
		}

		public IPlugin GetPluginInternal(string name)
		{
			return Plugins.Where(item => item.Metadata.Name == name).FirstOrDefault()?.Value;
		}

		private void _parts_CollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
		{
			switch (e.Action)
			{
				case NotifyCollectionChangedAction.Add:
				case NotifyCollectionChangedAction.Replace:
					foreach (string item in e.NewItems)
					{
						if (_parts.Count(p => p == item) > 1)
						{
							_parts.Remove(item);  // if there is duplication, remove one
							return;    // Remove will trigger this function, so it's recursive util there is no duplication
						}
					}
					break;
				case NotifyCollectionChangedAction.Remove:
				case NotifyCollectionChangedAction.Reset:
					break;
				default:
					throw new ArgumentOutOfRangeException($"{e.Action} is not supported.");
			}

			//_catalog.Catalogs.Clear();
			//foreach (var part in _parts)
			//{
			//	var catalog = GetCatalogFromFileOrDirectory(part);
			//	if (catalog == null)
			//		Logger.Error($"{part} is not a file or directory");
			//	else
			//		_catalog.Catalogs.Add(catalog);
			//}
			if (AllPlatform)
			{
				//_cppmanager.clearParts();
				//foreach (var part in _parts)
				//_cppmanager.addParts(part);
			}
			// Compose();
		}

		private ComposablePartCatalog GetCatalogFromFileOrDirectory(string path)
		{
			if (Directory.Exists(path))
			{
				return new DirectoryCatalog(path);
			}
			else if (File.Exists(path))
			{
				var asm = Assembly.LoadFile(path);
				return new AssemblyCatalog(asm);
			}
			else
				return null;
		}

		private object InvokeFactoryMethod(string name, params object[] p)
		{
			if (!AllPlatform)
				return null;
			var method = Factory.GetType().GetMethod(name);
			return method.Invoke(Factory, p);
		}
	}
}
