#include "stdafx.h"
#include "PluginManagerFactory.h"
#include <filesystem>

using namespace std;
namespace fs = filesystem;

namespace UPS {

	PluginManagerFactory::PluginManagerFactory()
	{
		clearGlobalParts();
		LPWSTR buf = new wchar_t[256];
		GetCurrentDirectory(256, buf);
		auto curdir = _wcsdup(buf);
		addGlobalPart(curdir);
		_managers.clear();
	}

	std::shared_ptr<PluginManagerFactory> PluginManagerFactory::getInstance()
	{
		//cout << "getInstance" << endl;
		//static PluginManagerFactory _singleton;
		static shared_ptr<PluginManagerFactory> _singleton(new PluginManagerFactory());
		return _singleton;
	}

	void PluginManagerFactory::addManager(std::shared_ptr<IPluginManager> manager)
	{
		//shared_ptr<IPluginManager> manager = initialManager;
		if (manager == nullptr)
			return;
		if (hasManager(manager))
			return;
		_managers[manager->type()] = manager;
		//_managers[manager->type()]->addPart(getCurrentDir());
	}

	void PluginManagerFactory::removeManager(IPluginManager* manager)
	{
		if (!hasManager(manager))
			return;
		_managers.erase(manager->type());
	}

	bool PluginManagerFactory::hasManager(const IPluginManager* manager)
	{
		auto search = _managers.find(manager->type());
		if (search != _managers.end()) {
			if (_managers[manager->type()].get() == manager)
				return true;
			else
			{
				//cout << "Manager " << manager->type() << " has two instances." << endl;
				return false;
			}
		}
		else
			return false;
	}

	bool PluginManagerFactory::hasManager(std::shared_ptr<IPluginManager> manager)
	{
		auto search = _managers.find(manager->type());
		if (search != _managers.end()) {
			if (manager == search->second)
				return true;
			else if (_managers[manager->type()].get() == manager.get())
				throw "duplicated shared_ptr detected, each manager should have the same shared_ptr instance, manager name: " + manager->type();
			else
			{
				//cout << "Manager " << manager->type() << " has two instances." << endl;
				return false;
			}
		}
		else
			return false;
	}

	PluginManagerFactory::~PluginManagerFactory()
	{
		//releaseAll(); //crashes
		//cout << "PluginManagerFactory destory" << endl;
	}

	void PluginManagerFactory::loadPluginManagers()
	{
		for (auto& part : _parts) {
			fs::path path(part);

			if (fs::is_regular_file(path) && lstrcmpi(path.extension().c_str(), L".dll") == 0) {
				loadPluginManager(path.c_str());
			}
			else if (fs::is_directory(path)) {
				for (auto& p : fs::directory_iterator(path)) {
					if (p.is_regular_file() && lstrcmpi(p.path().extension().c_str(), L".dll") == 0)
						loadPluginManager(p.path().c_str());
				};
			}
		}
	}

	void PluginManagerFactory::loadPluginManager(LPCWSTR filepath)
	{
		HINSTANCE mod = LoadLibrary(filepath);
		PluginManagerTypeFunc typefunc = (PluginManagerTypeFunc)GetProcAddress(mod, "pluginManagerType");
		CreatePluginManagerFunc createfunc = (CreatePluginManagerFunc)GetProcAddress(mod, "createPluginManager");
		DeletePluginManagerFunc deletefunc = (DeletePluginManagerFunc)GetProcAddress(mod, "deletePluginManager");
		if (typefunc == NULL || createfunc == NULL || deletefunc == NULL
			|| _managers.find(typefunc()) != _managers.end()) {
			FreeLibrary(mod);
		}
		else {
			try {
				createfunc(true);   //create will register itself in factory
				//_managers[typefunc()]->addPart(_curdir);
				//shared_ptr<IPluginManager> manager(createfunc(true), deletefunc);
				//manager->addPart(_curdir);
				//_managers.insert(make_pair(manager->type(), manager));
				//_managers[typefunc()] = manager;   // why deconstructor is triggered here???
				//manager->compose();
				_modules.emplace(mod);
			}
			catch (exception e)
			{
				cout << e.what() << endl;
				FreeLibrary(mod);
			}
		}
		return;
	}

	const std::vector<std::shared_ptr<IPluginManager>> PluginManagerFactory::getPluginManagers()
	{
		vector<shared_ptr<IPluginManager>> result;
		for (auto& kv : _managers)
			result.push_back(kv.second);
		return result;
	}

	shared_ptr<IPluginManager> PluginManagerFactory::getPluginManager(const std::string type)
	{
		return _managers[type];
	}

	const std::vector<std::shared_ptr<IPlugin>> PluginManagerFactory::getAllPlugins()
	{
		vector<shared_ptr<IPlugin>> result;
		for (auto& kv : _managers) {
			auto manager = kv.second;
			for (auto plugin : manager->getPlugins())
				result.push_back(plugin);
		}
		return result;
	}

	const std::vector<std::wstring> PluginManagerFactory::getAllPluginNames()
	{
		vector<wstring> result;
		for (auto& kv : _managers) {
			auto manager = kv.second;
			for (auto name : manager->getPluginNames())
				result.push_back(name);
		}
		return result;
	}

	const std::shared_ptr<IPlugin> PluginManagerFactory::getPlugin(const std::wstring name)
	{
		for (auto& kv : _managers) {
			auto plugin = kv.second->getPluginInternal(name);
			if (plugin == nullptr)
				continue;
			else
				return plugin;
		}
		return nullptr;
	}

	void PluginManagerFactory::releaseAll()
	{
		for (auto& kv : _managers) {
			kv.second->releasePlugins();
		}
		_managers.clear();
		for (auto& mod : _modules) {
			FreeLibrary(mod);
		}
		_modules.clear();
	}

	std::vector<std::wstring> PluginManagerFactory::getGlobalParts()
	{
		return vector<wstring>(_parts.begin(), _parts.end());
	}

	void PluginManagerFactory::addGlobalPart(std::wstring part)
	{
		_parts.emplace(part);
	}

	void PluginManagerFactory::removeGlobalPart(std::wstring part)
	{
		auto iter = find_if(_parts.begin(), _parts.end(), [part](wstring part2) -> bool { return part == part2; });
		if (iter != _parts.end())
			_parts.erase(iter);
	}

	void PluginManagerFactory::clearGlobalParts()
	{
		_parts.clear();
	}

	//std::wstring PluginManagerFactory::getCurrentDir()
	//{
	//	return _curdir;
	//}

	//void PluginManagerFactory::setCurrentDir(const std::wstring dir)
	//{
	//	_curdir = dir;
	//}

	void PluginManagerFactory::composeAll()
	{
		for (auto& kv : _managers)
			kv.second->compose();
	}

}
