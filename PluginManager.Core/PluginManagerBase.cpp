#include "stdafx.h"
#include "PluginManagerBase.h"
#include <algorithm>

using namespace std;
using namespace UPS;

UPS::PluginManagerBase::PluginManagerBase(bool allplatform, std::string type)
	:IPluginManager()
{
	_allplatform = allplatform;
	_type = type;
	//_pluginNames.clear();
	_parts.clear();
}


UPS::PluginManagerBase::~PluginManagerBase()
{
	if (getFactory() != nullptr) {
		getFactory()->removeManager(this);
	}
}

bool UPS::PluginManagerBase::isAllPlatform() const
{
	return _allplatform;
}

std::vector<std::shared_ptr<UPS::IPlugin>> UPS::PluginManagerBase::getAllPlugins() const
{
	if (isAllPlatform())
		return getFactory()->getAllPlugins();
	else
		return getPlugins();
}

std::vector<std::shared_ptr<UPS::IPlugin>> UPS::PluginManagerBase::getPlugins() const
{
	vector<shared_ptr<IPlugin>> result;
	for (auto& name : getAllPluginNames())
		result.push_back(getPlugin(name));
	return result;
}

std::vector<std::wstring> UPS::PluginManagerBase::getAllPluginNames() const
{
	if (isAllPlatform())
		return getFactory()->getAllPluginNames();
	else
		return getPluginNames();
}

std::shared_ptr<IPlugin> UPS::PluginManagerBase::getPlugin(std::wstring name) const
{
	auto plugin = getPluginInternal(name);
	if (plugin != nullptr)
		return plugin;
	else if(isAllPlatform())
		return getFactory()->getPlugin(name);
	return nullptr;
}

std::vector<std::wstring> UPS::PluginManagerBase::getParts() const
{
	set<wstring> result(_parts.begin(), _parts.end());
	if (isAllPlatform())
		for (auto p : getFactory()->getGlobalParts())
			result.emplace(p);
	return vector<wstring>(result.begin(), result.end());
}

void UPS::PluginManagerBase::addPart(const std::wstring & part)
{
	//auto duplicate = find_if(_parts.begin(), _parts.end(), [part](wstring part2) -> bool { return part == part2; });
	//if (duplicate != _parts.end())
	//	return;
	_parts.emplace(part);
}

void UPS::PluginManagerBase::removePart(const std::wstring & part)
{
	auto iter = find_if(_parts.begin(), _parts.end(), [part](wstring part2) -> bool { return part == part2; });
	if (iter != _parts.end())
		_parts.erase(iter);
	if(isAllPlatform())
		getFactory()->removeGlobalPart(part);
}

void UPS::PluginManagerBase::clearParts()
{
	_parts.clear();
	//releasePlugins();
}

const std::string UPS::PluginManagerBase::type() const
{
	return _type;
}

void UPS::PluginManagerBase::composeAll()
{
	if (isAllPlatform())
		getFactory()->composeAll();
	else
		compose();
}

std::shared_ptr<PluginManagerFactory> UPS::PluginManagerBase::getFactory() const
{
	return _factory;
}
