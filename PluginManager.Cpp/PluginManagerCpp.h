#pragma once
#include "../PluginManager.Core/PluginManagerBase.h"
#include <iostream>
#include <vector>

#ifdef PLUGINMANAGERCPP_EXPORTS
#define DLL __declspec(dllexport)
#define DLLAPI EXTERN_C __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#define DLLAPI EXTERN_C __declspec(dllimport)
#endif

namespace UPS
{
	namespace Cpp
	{
		class DLL PluginManagerCpp
			: public UPS::PluginManagerBase
		{
		public:
			static PluginManagerCpp* createManager(bool allplatform);
			static void deleteManager(PluginManagerCpp* manager);
			// Inherited via PluginManagerBase
			virtual void setAllPlatform(bool allplatform) override;
			virtual void compose() override;
			virtual void releasePlugins() override;
			virtual std::vector<std::wstring> getPluginNames() const override;
			virtual std::shared_ptr<IPlugin> getPluginInternal(std::wstring name) const override;

		private:
			PluginManagerCpp(bool allplatform);
			~PluginManagerCpp();
			void loadPlugin(const WCHAR* path);

			std::unordered_map<std::wstring, std::shared_ptr<IPlugin>> _plugins;
			std::set<HINSTANCE> _modules;
		};
	}
}

