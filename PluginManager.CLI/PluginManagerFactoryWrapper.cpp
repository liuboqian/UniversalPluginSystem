#include "stdafx.h"
#include "PluginManagerFactoryWrapper.h"
#include "CSharpPluginAdapter.h"
#include "Utility.h"

using namespace std;
using namespace UPS;

UPS::CLI::PluginManagerFactoryWrapper::PluginManagerFactoryWrapper()
{
	//_factory = &(PluginManagerFactory::getInstance());
}

UPS::CLI::PluginManagerFactoryWrapper::~PluginManagerFactoryWrapper()
{
	//delete _factory;
}

void UPS::CLI::PluginManagerFactoryWrapper::loadPluginManagers()
{
	getInstance()->loadPluginManagers();
}

cli::array<UPS::CSharp::IPlugin^>^ UPS::CLI::PluginManagerFactoryWrapper::getAllPlugins()
{
	auto names = getAllPluginNames();
	cli::array<UPS::CSharp::IPlugin^>^ result = gcnew cli::array<UPS::CSharp::IPlugin^>(names->Length);
	for (int i = 0; i < names->Length; i++) {
		result[i] = getPlugin(names[i]);
	}
	return result;
}

cli::array<System::String^>^ UPS::CLI::PluginManagerFactoryWrapper::getAllPluginNames()
{
	auto names = getInstance()->getAllPluginNames();
	cli::array<System::String^>^ result = gcnew cli::array<System::String^>(names.size());
	int index = 0;
	for (auto& name : names) {
		result[index++] = UtilityEx::wstring2CSString(name);
	}
	return result;
}

UPS::CSharp::IPlugin ^ UPS::CLI::PluginManagerFactoryWrapper::getPlugin(System::String ^ name)
{
	wstring wname = UtilityEx::CSString2wstring(name);
	auto plugin = getInstance()->getPlugin(wname);
	if (plugin == nullptr)
		return nullptr;
	auto adapter = dynamic_cast<CSharpPluginAdapter*>(plugin.get());
	if (adapter != nullptr) {  // it is a managed plugin, so get its raw object
		return adapter->get();
	}
	else {    // it's not a managed plugin, so need a wrapper
		return gcnew CppPluginAdapter(&plugin);  // this function pass in a pointer, but it will add ref count
	}
}

void UPS::CLI::PluginManagerFactoryWrapper::releaseAll()
{
	getInstance()->releaseAll();
}

//System::String ^ UPS::CLI::PluginManagerFactoryWrapper::getCurrentDir()
//{
//	return UtilityEx::wstring2CSString(getInstance()->getCurrentDir());
//}
//
//void UPS::CLI::PluginManagerFactoryWrapper::setCurrentDir(System::String ^ dir)
//{
//	getInstance()->setCurrentDir(UtilityEx::CSString2wstring(dir));
//}

void UPS::CLI::PluginManagerFactoryWrapper::composeAll()
{
	getInstance()->composeAll();
}

cli::array<System::String^>^ UPS::CLI::PluginManagerFactoryWrapper::getGlobalParts()
{
	auto parts = getInstance()->getGlobalParts();
	cli::array<System::String^>^ result = gcnew cli::array<System::String^>(parts.size());
	int index = 0;
	for (auto& part : parts) {
		result[index++] = UtilityEx::wstring2CSString(part);
	}
	return result;
}

void UPS::CLI::PluginManagerFactoryWrapper::addGlobalPart(System::String ^ part)
{
	getInstance()->addGlobalPart(UtilityEx::CSString2wstring(part));
}

void UPS::CLI::PluginManagerFactoryWrapper::removeGlobalPart(System::String ^ part)
{
	getInstance()->removeGlobalPart(UtilityEx::CSString2wstring(part));
}

void UPS::CLI::PluginManagerFactoryWrapper::clearGlobalPart()
{
	getInstance()->clearGlobalParts();
}

std::shared_ptr<UPS::PluginManagerFactory> UPS::CLI::PluginManagerFactoryWrapper::getInstance()
{
	return PluginManagerFactory::getInstance();
}
