#include "stdafx.h"
#include "CppPluginAdapter.h"
#include "Utility.h"

using namespace std;

UPS::CLI::CppPluginAdapter::CppPluginAdapter(std::shared_ptr<UPS::IPlugin>* plugin)
{
	if (plugin == nullptr)
		throw "plugin cannot be null - CppPluginAdapter";
	_plugin = new shared_ptr<IPlugin>(*plugin);  // manually create a shared_ptr, because managed class can't have unmanaged stack object
}

UPS::CLI::CppPluginAdapter::~CppPluginAdapter()
{
	delete _plugin;
}

std::shared_ptr<UPS::IPlugin> UPS::CLI::CppPluginAdapter::get()
{
	return *_plugin;
}

System::String ^ UPS::CLI::CppPluginAdapter::Name()
{
	return UtilityEx::wstring2CSString((*_plugin)->name());
}

void UPS::CLI::CppPluginAdapter::Set(System::String ^param)
{
	(*_plugin)->set(UtilityEx::CSString2wstring(param));
}

void UPS::CLI::CppPluginAdapter::Unset(System::String ^param)
{
	(*_plugin)->unset(UtilityEx::CSString2wstring(param));
}

System::String ^ UPS::CLI::CppPluginAdapter::Invoke(System::String ^param)
{
	auto result=(*_plugin)->invoke(UtilityEx::CSString2wstring(param));
	return UtilityEx::wstring2CSString(result);
}
