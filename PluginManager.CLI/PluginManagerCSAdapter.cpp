#include "stdafx.h"
#include "PluginManagerCSAdapter.h"
#include "PluginManagerFactoryWrapper.h"
#include "Utility.h"

using namespace std;
using namespace UPS;
using namespace UPS::CLI;
using namespace System::Runtime::InteropServices;


PluginManagerCSAdapter::PluginManagerCSAdapter(bool allplatform)
	: PluginManagerBase(allplatform, "CSharp")
{
	setAllPlatform(allplatform);
}

UPS::CLI::PluginManagerCSAdapter::~PluginManagerCSAdapter()
{
	cout << "PluginManagerCSAdapter destory" << endl;
}

PluginManagerCSAdapter * UPS::CLI::PluginManagerCSAdapter::createPluginManager(bool allplatform)
{
	return new PluginManagerCSAdapter(allplatform);
}

void UPS::CLI::PluginManagerCSAdapter::deletePluginManager(PluginManagerCSAdapter * manager)
{
	delete manager;
}

void UPS::CLI::PluginManagerCSAdapter::injectCSManager(intptr_t manager)
{
	auto handle = GCHandle::FromIntPtr(System::IntPtr(manager)).Target;
	CSharp::PluginManagerCSharp^ csmanager = (CSharp::PluginManagerCSharp^)handle;

	_csmanager = csmanager;
	_csmanager->Factory = _factoryWrapper.get();
	_csmanager->Wrapper = System::IntPtr::IntPtr((void*)this);
}

std::shared_ptr<IPlugin> UPS::CLI::PluginManagerCSAdapter::getPluginInternal(std::wstring name) const
{
	CSharp::IPlugin^ plugin = _csmanager->GetPluginInternal(UtilityEx::wstring2CSString(name));
	if (plugin == nullptr)
		return nullptr;
	else
		return make_shared<CSharpPluginAdapter>(plugin);
}

void UPS::CLI::PluginManagerCSAdapter::compose()
{
	_csmanager->Compose();
	//_pluginNames.clear();
	//cli::array<System::String^>^ names = _csmanager->PluginNames;
	//for (int i = 0; i < names->Length; i++) {
	//	_pluginNames.emplace(UtilityEx::CSString2wstring(names[i]));
	//}
}

void UPS::CLI::PluginManagerCSAdapter::releasePlugins()
{
}

std::vector<std::wstring> UPS::CLI::PluginManagerCSAdapter::getPluginNames() const
{
	std::vector<wstring> result;
	auto names = _csmanager->PluginNames;
	for (int i = 0; i < names->Length; i++) {
		result.push_back(UtilityEx::CSString2wstring(names[i]));
	}
	return result;
}

void UPS::CLI::PluginManagerCSAdapter::setAllPlatform(bool allplatform)
{
	_allplatform = allplatform;
	if (allplatform)
	{
		if (_factoryWrapper.get() == nullptr) {
			_factoryWrapper = gcnew PluginManagerFactoryWrapper();
		}

		if (_csmanager.get() == nullptr) {
			_csmanager = gcnew UPS::CSharp::PluginManagerCSharp(false);
		}
		if (_csmanager->Wrapper == System::IntPtr::Zero) {
			_csmanager->Wrapper = System::IntPtr::IntPtr((void*)this);
		}
		if (_csmanager->Factory == nullptr) {
			_csmanager->Factory = _factoryWrapper.get();
		}
		_csmanager->AllPlatform = true;

		_factory = _factoryWrapper->getInstance();
		if (!_factory->hasManager(this))
			_factory->addManager(shared_ptr<IPluginManager>(this, deletePluginManager));
		_factory->loadPluginManagers();
	}
	//compose();
}

void UPS::CLI::PluginManagerCSAdapter::addPart(const std::wstring & part)
{
	System::String^ partname(UtilityEx::wstring2CSString(part));
	_csmanager->Parts->Add(partname);
}

void UPS::CLI::PluginManagerCSAdapter::removePart(const std::wstring & part)
{
	System::String^ partname(UtilityEx::wstring2CSString(part));
	_csmanager->Parts->Remove(partname);
}

void UPS::CLI::PluginManagerCSAdapter::clearParts()
{
	_csmanager->Parts->Clear();
}
