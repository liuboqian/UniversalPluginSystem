#pragma once
#include "IPluginManager.h"
#include <unordered_map>
#include <set>
#include <initializer_list>

namespace UPS {
	class DLL PluginManagerFactory
	{
	public:
		static std::shared_ptr<PluginManagerFactory> getInstance();
		// initialManager will be registed to this factory, the shared_ptr should be create by manager itself and contain a proper deleter
		void addManager(std::shared_ptr<IPluginManager> manager);
		void removeManager(IPluginManager* manager);  // will remove the instance if it exist
		bool hasManager(const IPluginManager* manager);  // compare pointer
		bool hasManager(std::shared_ptr<IPluginManager> manager);
		virtual ~PluginManagerFactory();
		void loadPluginManagers();  // load all plugin managers in this folder, won't be loaded if they don't have the three global functions or already been loaded
		const std::vector<std::shared_ptr<IPluginManager>> getPluginManagers();
		std::shared_ptr<IPluginManager> getPluginManager(const std::string type);
		const std::vector<std::shared_ptr<IPlugin>> getAllPlugins();
		const std::vector<std::wstring> getAllPluginNames();
		const std::shared_ptr<IPlugin> getPlugin(const std::wstring name);
		void releaseAll();
		std::vector<std::wstring> getGlobalParts();
		void addGlobalPart(std::wstring part);
		void removeGlobalPart(std::wstring part);
		void clearGlobalParts();
		void composeAll();

	protected:
		void loadPluginManager(LPCWSTR path);
		PluginManagerFactory();

		std::unordered_map<std::string, std::shared_ptr<IPluginManager>> _managers;
		std::set<HINSTANCE> _modules;   // _modules will load all pluginmanager under curdir, but it's not an accurate map to _managers
		std::set<std::wstring> _parts;  // global parts

		//static shared_ptr<PluginManagerFactory> _singleton;
	};
}

