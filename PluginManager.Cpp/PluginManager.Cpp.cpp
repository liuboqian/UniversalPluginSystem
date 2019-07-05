// PluginManager.Cpp.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "PluginManagerCpp.h"


DLLAPI const char* pluginManagerType() {
	return "C++";
};

DLLAPI UPS::IPluginManager* createPluginManager(bool allplatform) {
	return UPS::Cpp::PluginManagerCpp::createManager(allplatform);
}

DLLAPI void deletePluginManager(UPS::IPluginManager * manager)
{
	UPS::Cpp::PluginManagerCpp* cppmanager = dynamic_cast<UPS::Cpp::PluginManagerCpp*>(manager);
	if (cppmanager != NULL)
		UPS::Cpp::PluginManagerCpp::deleteManager(cppmanager);
	else
		std::cout << "PluginManagerCpp should be deleted by its own dll!" << std::endl;
}

