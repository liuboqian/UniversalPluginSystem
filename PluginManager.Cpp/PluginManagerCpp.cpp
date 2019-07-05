#include "stdafx.h"
#include "PluginManagerCpp.h"
#include <algorithm>
#include <fstream>
#include <direct.h>
#include <filesystem>
#include "../PluginManager.Core/Utility.h"

using namespace std;
namespace fs = filesystem;

namespace UPS
{
  namespace Cpp
  {
    PluginManagerCpp::PluginManagerCpp(bool allplatform)
      :PluginManagerBase(allplatform, "C++")
    {
      _modules.clear();

      // Add current dir
      LPWSTR buf = new wchar_t[256];
      GetCurrentDirectory(256, buf);
      LPWSTR curdir = _wcsdup(buf);
      _parts.emplace(curdir);

      setAllPlatform(allplatform);
    }

    PluginManagerCpp::~PluginManagerCpp()
    {
      releasePlugins();
      //cout << "PluginManagerCpp destory" << endl;
    }

    PluginManagerCpp * PluginManagerCpp::createManager(bool allplatform)
    {
      return new UPS::Cpp::PluginManagerCpp(allplatform);
    }

    void PluginManagerCpp::deleteManager(PluginManagerCpp * manager)
    {
      delete manager;
    }

    void PluginManagerCpp::setAllPlatform(bool allplatform)
    {
      _allplatform = allplatform;
      if (allplatform)
      {
        _factory = PluginManagerFactory::getInstance();
        if (!_factory->hasManager(this))
          _factory->addManager(shared_ptr<IPluginManager>(this, deleteManager));
        _factory->loadPluginManagers();
      }
      //compose();
    }

    std::shared_ptr<IPlugin> PluginManagerCpp::getPluginInternal(std::wstring name) const
    {
      if (_plugins.find(name) != _plugins.end())
        return _plugins.at(name);
      else
        return nullptr;
    }

    void PluginManagerCpp::compose()
    {
      releasePlugins();

      for (auto& part : getParts()) {
        loadPlugin(part.c_str());
        //fstream file;
        //file.open(part, ios::in || ios::binary);
        //DWORD ftyp = GetFileAttributes(part);
        //if (ftyp == FILE_ATTRIBUTE_DIRECTORY)
      }
    }

    void PluginManagerCpp::releasePlugins()
    {
      //for (int i = 0; i < _plugins.size(); i++) {
      //	HINSTANCE mod = _modules[i];   // wrong, modules is not mapped to plugins
      //	IPlugin* plugin = _plugins[i];
      //	auto deleter = (DeletePluginFunc)GetProcAddress(mod, "Delete");
      //	if (deleter != NULL) {
      //		throw runtime_error("Can't release a plugin");
      //		deleter(plugin);
      //	}
      //	FreeLibrary(mod);
      //}
      for (auto& kv : _plugins)
        kv.second.reset(); // reset all smart pointer, so after release, managers and dll can be safely destroy
      _plugins.clear();
      //_pluginNames.clear();
      for (auto mod : _modules)
        FreeLibrary(mod);
      _modules.clear();
    }

    std::vector<std::wstring> PluginManagerCpp::getPluginNames() const
    {
      vector<wstring> result;
      for (auto& kv : _plugins)
        result.push_back(kv.first);
      return result;
    }

    void PluginManagerCpp::loadPlugin(const WCHAR* filepath)
    {
      fs::path path(filepath);
      if (fs::is_regular_file(path)) {
        if (lstrcmpW(path.extension().c_str(), L".dll") != 0)
          return;
        HINSTANCE mod = LoadLibrary(path.c_str());
        if (!mod)
        {
          wstring emsg = L"Can't load dll file: ";
          emsg += path.c_str();
          //cout << Utility::wstring2string(emsg) << endl;
        }
        auto nameFunc = (NameFunc)GetProcAddress(mod, "name");
        auto createFunc = (CreatePluginFunc)GetProcAddress(mod, "createPlugin");
        auto deleteFunc = (DeletePluginFunc)GetProcAddress(mod, "deletePlugin");
        if (nameFunc != NULL && createFunc != NULL && deleteFunc != NULL)
        {
          _modules.emplace(mod);
          _plugins[nameFunc()] = shared_ptr<IPlugin>(createFunc(), [deleteFunc](IPlugin* plugin) {deleteFunc(plugin); });
          //_pluginNames.emplace(nameFunc());
        }
        else
          FreeLibrary(mod);
      }
      else if (fs::is_directory(path)) {
        for (auto& file : fs::directory_iterator(path))
          loadPlugin(file.path().c_str());
      }
      else {
        wstring errormsg(filepath);
        errormsg += L" is not a directory or file";
        wcout << errormsg;
        return;
      }
    }
  }
}
