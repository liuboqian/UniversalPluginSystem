// PluginManager.Python.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "../PluginManager.Core/IPluginManager.h"
#include "PluginManagerPython.h"

DLLAPI const char* pluginManagerType() {
  return "Python";
};

DLLAPI UPS::IPluginManager* createPluginManager(bool allplatform) {
  return UPS::Python::PluginManagerPython::createManager(allplatform);
}

DLLAPI void deletePluginManager(UPS::IPluginManager * manager)
{
  UPS::Python::PluginManagerPython* cppmanager = dynamic_cast<UPS::Python::PluginManagerPython*>(manager);
  if (cppmanager != NULL)
    UPS::Python::PluginManagerPython::deleteManager(cppmanager);
  else
    std::cout << "PluginManagerCpp should be deleted by its own dll!" << std::endl;
}



