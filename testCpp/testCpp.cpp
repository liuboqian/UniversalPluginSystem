
#include "pch.h"
#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include "Singleton.h"
#include "../PluginManager.Core/PluginManagerFactory.h"
#include "../PluginManager.Core/PluginManagerDLL.h"
#include "../include/python/include/Python.h"

using namespace std;

//extern "C" __declspec(dllimport) UPS::IPluginManager* createPluginManager(bool allplatform);

int main()
{
	//auto* manager = createPluginManager(true);
	//manager->composeAll();
	//auto names = manager->getAllPluginNames();
	//auto plugin = manager->getPlugin(names[0]);

	//auto* manager2 = createPluginManager(true);
	//manager2->composeAll();

  Py_Initialize();
  PyRun_SimpleString("a='test'");
  //auto* manager = createPluginManager(false);

	//manager->releasePlugins();
	//deletePluginManager(manager);

	//set<string> collection;
	//string key = "a";
	//collection.emplace(key);
	//key = "b";
	//collection.emplace(key);
	//collection.emplace(key);
	//collection.emplace(key);

	//for (auto kv : collection)
	//	cout << kv.c_str() << endl;

	//unordered_map<string, int*> map;
	//map["a"] = new int(1);
	//map["b"] = new int(2);
	//map["c"] = new int(3);
	//cout << *map["b"] << endl;
	//cout << *map["d"] << endl;

	//auto singleton = Singleton::Create();
	//auto singleton2 = Singleton::Create();

	system("pause");
}
