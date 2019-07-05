// PluginSampleCpp.cpp : Defines the exported functions for the DLL application.
//


#include "stdafx.h"

#include "DivideCalculator.h"

#ifdef PLUGINSAMPLECPP_EXPORTS
#define DLL __declspec(dllexport)
#define DLLAPI EXTERN_C __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#define DLLAPI EXTERN_C __declspec(dllimport)
#endif

DLLAPI std::wstring name() {
	return L"DivideCalculator";
}


DLLAPI UPS::IPlugin* createPlugin() {
	return new DivideCalculator();
}


DLLAPI void deletePlugin(UPS::IPlugin* plugin) {
	delete plugin;
}