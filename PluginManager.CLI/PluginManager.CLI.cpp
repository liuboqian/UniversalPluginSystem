// PluginManager.CLI.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include "PluginManagerCSAdapter.h"

#ifdef PLUGINMANAGERCLI_EXPORTS
#define DLL __declspec(dllexport)
#define DLLAPI EXTERN_C __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#define DLLAPI EXTERN_C __declspec(dllimport)
#endif

DLLAPI const char* pluginManagerType() {
	return "CSharp";
};

DLLAPI UPS::IPluginManager* createPluginManager(bool allplatform) {
	return UPS::CLI::PluginManagerCSAdapter::createPluginManager(allplatform);
}

DLLAPI void deletePluginManager(UPS::IPluginManager * manager) {
	UPS::CLI::PluginManagerCSAdapter* csmanager = dynamic_cast<UPS::CLI::PluginManagerCSAdapter*>(manager);
	if (csmanager != NULL)
		UPS::CLI::PluginManagerCSAdapter::deletePluginManager(csmanager);
	else
		std::cout << "PluginManagerCSharp should be deleted by its own dll!" << std::endl;
}

// call from CSharp side, will instantiate factory object and set to csharp manager
DLLAPI void injectManager(intptr_t wrapper, intptr_t manager) {
	//auto* csadapter = UPS::CLI::PluginManagerCSAdapter::createPluginManager(false);
	auto* csadapter = (UPS::CLI::PluginManagerCSAdapter*)(void*)wrapper;
	csadapter->injectCSManager(manager);
	csadapter->setAllPlatform(true);
}
