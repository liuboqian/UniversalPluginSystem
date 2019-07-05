#include "stdafx.h"
#include "CSharpPluginAdapter.h"
#include "Utility.h"
using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;


UPS::CLI::CSharpPluginAdapter::CSharpPluginAdapter(UPS::CSharp::IPlugin^ plugin)
	:_plugin(plugin)
{
}


UPS::CLI::CSharpPluginAdapter::~CSharpPluginAdapter()
{
	// do we need to FreeHGlobal here?
}

UPS::CSharp::IPlugin ^ UPS::CLI::CSharpPluginAdapter::get()
{
	return _plugin.get();
}

const std::wstring UPS::CLI::CSharpPluginAdapter::name()
{
	//auto name = _plugin->Name();
	//_name = marshal_as<char*>(name);  // marshal_as will cause compiler error
	auto name = _plugin->Name();
	return UtilityEx::CSString2wstring(name);
}

void UPS::CLI::CSharpPluginAdapter::set(const std::wstring & param)
{
	_plugin->Set(UtilityEx::wstring2CSString(param));
}

void UPS::CLI::CSharpPluginAdapter::unset(const std::wstring & param)
{
	_plugin->Unset(UtilityEx::wstring2CSString(param));
}

const std::wstring UPS::CLI::CSharpPluginAdapter::invoke(const std::wstring & param)
{
	auto result = _plugin->Invoke(UtilityEx::wstring2CSString(param));
	return UtilityEx::CSString2wstring(result);
}
