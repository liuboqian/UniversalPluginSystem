#pragma once
#include "IPluginManager.h"
#include "PluginManagerFactory.h"
#include <set>
#include <unordered_map>

namespace UPS {
	// base class of PluginManager, PluginManager could derived from this class, but it's not mandatory
	class DLL PluginManagerBase	: 
		public IPluginManager
	{
	public:
		PluginManagerBase(bool allplatform, std::string type);
		virtual ~PluginManagerBase();

		// Inherited via IPluginManager
		virtual bool isAllPlatform() const override;
		//virtual void setAllPlatform(bool allplatform) override;
		virtual std::vector<std::shared_ptr<IPlugin>> getAllPlugins() const override;
		virtual std::vector<std::wstring> getAllPluginNames() const override;
		virtual std::shared_ptr<IPlugin> getPlugin(std::wstring name) const override;
		virtual std::vector<std::wstring> getParts() const override;  // get local parts and global parts, dependes on isAllplatform
		virtual void addPart(const std::wstring & part) override;
		virtual void removePart(const std::wstring & part) override;
		virtual void clearParts() override;
		virtual void composeAll() override;
		virtual std::shared_ptr<PluginManagerFactory> getFactory() const override;
	
		//virtual void compose() override;   // must implement by derived class
		//virtual void releasePlugins() override;
		virtual std::vector<std::shared_ptr<IPlugin>> getPlugins() const override;
		//virtual const std::vector<std::wstring> getPluginNames() const override;
		//virtual std::shared_ptr<IPlugin> getPluginInternal(std::wstring name) const override;
		virtual const std::string type() const override;

	protected:
		bool _allplatform;
		std::set<std::wstring> _parts;
		//std::set<std::wstring> _pluginNames;
		std::shared_ptr<PluginManagerFactory> _factory;
		std::string _type;
	};
}

