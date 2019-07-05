#pragma once

#include <iostream>

#ifdef PLUGINMANAGERCORE_EXPORTS
#define DLL __declspec(dllexport)
#define DLLAPI EXTERN_C __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#define DLLAPI EXTERN_C __declspec(dllimport)
#endif

namespace UPS
{
		class DLL IPlugin
		{
		public:
			virtual const std::wstring name() = 0;
			virtual void set(const std::wstring& param) = 0;
			virtual void unset(const std::wstring& param) = 0;
			virtual const std::wstring invoke(const std::wstring& param) = 0;
		};

		// The dll should also provide these global functions, 
		// you can implement CreatePlugin as singleton if you want to
		// std::wstring name();
		typedef std::wstring(__cdecl *NameFunc)(void);
		// UPS::IPlugin* createPlugin();
		typedef IPlugin*(__cdecl *CreatePluginFunc)(void);
		// void deletePlugin(UPS::IPlugin* plugin);
		typedef void(__cdecl *DeletePluginFunc)(UPS::IPlugin*);
}
