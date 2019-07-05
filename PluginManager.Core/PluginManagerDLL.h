#pragma once
#include "PluginManagerFactory.h"

extern "C" __declspec(dllimport) const char* pluginManagerType();

extern "C" __declspec(dllimport) UPS::IPluginManager* createPluginManager(bool allplatform);

extern "C" __declspec(dllimport) void deletePluginManager(UPS::IPluginManager * manager);

