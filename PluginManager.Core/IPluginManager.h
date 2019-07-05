#pragma once
#include <vector>
#include <iostream>
#include "IPlugin.h"
#include <set>

namespace UPS
{
	class PluginManagerFactory;

	// you should never call getAllXXX inside a getXXX function ,that will cause stack overflow
	class DLL IPluginManager
	{
	public:
		virtual bool isAllPlatform() const = 0;
		// setAllPlatform should create/get the factory and register itself to the factory
		virtual void setAllPlatform(bool allplatform) = 0;

		virtual std::vector<std::shared_ptr<IPlugin>> getAllPlugins() const = 0;
		virtual std::vector<std::wstring> getAllPluginNames() const = 0;
		virtual std::shared_ptr<IPlugin> getPlugin(std::wstring name) const = 0;
		virtual std::vector<std::wstring> getParts() const = 0;
		virtual void addPart(const std::wstring& part) = 0;
		virtual void removePart(const std::wstring& part) = 0;  // you could remove local or global part
		virtual void clearParts() = 0;   // only clear local parts
		virtual void composeAll() = 0;
		virtual std::shared_ptr<PluginManagerFactory> getFactory() const = 0;

		// the following method should only concern things within this manager
		virtual void compose() = 0;
		virtual void releasePlugins() = 0;
		virtual std::vector<std::shared_ptr<IPlugin>> getPlugins() const = 0;
		virtual std::vector<std::wstring> getPluginNames() const = 0;
		virtual std::shared_ptr<IPlugin> getPluginInternal(std::wstring name) const = 0;
		virtual const std::string type() const = 0;   // type must be different, it's the identifier of PluginManager
	};

	// The dll should also provide these global functions,
	// CreatePluginManager should be singleton, and will register itself in factory
	// const char* pluginManagerType();
	typedef const char*(__cdecl *PluginManagerTypeFunc)();
	// UPS::IPluginManager* createPluginManager(bool allplatform);
	// don't manually delete this pointer if allplatform is true, PluginManagerFactory will take care of it
	typedef UPS::IPluginManager*(__cdecl *CreatePluginManagerFunc)(bool);
	// void deletePluginManager(UPS::IPluginManager* manager);
	typedef void(__cdecl *DeletePluginManagerFunc)(UPS::IPluginManager*);
}
