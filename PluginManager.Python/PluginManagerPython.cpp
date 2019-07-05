#include "stdafx.h"
#include "PluginManagerPython.h"
#include <filesystem>
#include <sstream>
#include "../PluginManager.Core/Utility.h"
#include "UtilityEx.h"

using namespace std;
using namespace UPS;
namespace fs = filesystem;

UPS::Python::PluginManagerPython::PluginManagerPython(bool allplatform)
  : PluginManagerBase(allplatform, "Python")
{
  _modules.clear();
}


UPS::Python::PluginManagerPython::~PluginManagerPython()
{
  releasePlugins();
}

UPS::Python::PluginManagerPython * UPS::Python::PluginManagerPython::createManager(bool allplatform)
{
  return new PluginManagerPython(allplatform);
}

void UPS::Python::PluginManagerPython::deleteManager(PluginManagerPython * manager)
{
  delete manager;
}

void UPS::Python::PluginManagerPython::setAllPlatform(bool allplatform)
{
  _allplatform = allplatform;
  if (allplatform)
  {
    _factory = PluginManagerFactory::getInstance();
    if (!_factory->hasManager(this))
      _factory->addManager(shared_ptr<IPluginManager>(this, [](IPluginManager* manager)->void {delete manager; }));
    _factory->loadPluginManagers();
  }
}

void UPS::Python::PluginManagerPython::compose()
{
  releasePlugins();
  if (!Py_IsInitialized())
    Py_Initialize();
  PyRun_SimpleString("import sys");

  for (auto part : getParts()) {
    loadPyFile(part.c_str());
  }
}

void UPS::Python::PluginManagerPython::releasePlugins()
{
  _modules.clear();
}

std::vector<std::wstring> UPS::Python::PluginManagerPython::getPluginNames() const
{
  vector<wstring> result;
  for (auto& kv : _modules)
    result.push_back(kv.first);
  return result;
}

std::shared_ptr<IPlugin> UPS::Python::PluginManagerPython::getPluginInternal(std::wstring name) const
{
  try {
    auto* mod = _modules.at(name).get();
    auto* func = PyObject_GetAttrString(mod, "createPlugin");
    auto* pyobject = PyObject_CallFunction(func, NULL);
    return make_shared<PyPluginAdapter>(pyobject);
  }
  catch (exception e) {
    cout << "Failed at loading script \"" << name.c_str() << "\"" << e.what() << endl;
  }
}

void UPS::Python::PluginManagerPython::loadPyFile(const WCHAR * filepath)
{
  fs::path path(filepath);

  if (fs::is_regular_file(path)) {
    if (lstrcmp(path.extension().c_str(), L".py") != 0)
      return;
    try {
      ostringstream stringstream;
      stringstream << "sys.path.append(r\"" << Utility::wchars2chars(path.parent_path().c_str()) << "\")";
      PyRun_SimpleString(stringstream.str().c_str());
      auto moduleName = Utility::wchars2chars(path.stem().c_str());
      PyObject* pModule = PyImport_ImportModule(moduleName.get());
      if (pModule == NULL)
        return;
      PyObject* pNameFunc = PyObject_GetAttrString(pModule, "name");
      auto* nameobj = PyObject_CallFunction(pNameFunc, NULL);
      auto name = UtilityEx::pyObject2wstring(nameobj);
      _modules[name] = shared_ptr<PyObject>(
        pModule,
        [](PyObject* obj)->void {Py_XDECREF(obj); });
    }
    catch (exception e) {
      cout << e.what() << endl;
    }
  }
  else if (fs::is_directory(path)) {
    for (auto& file : fs::directory_iterator(path)) {
      loadPyFile(file.path().c_str());
    }
  }
  else {
    wstring errormsg(filepath);
    errormsg += L" is not a directory or file";
    wcout << errormsg;
    return;
  }
}
