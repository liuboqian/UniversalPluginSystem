#include "stdafx.h"
#include "PyPluginAdapter.h"
#include "../PluginManager.Core/Utility.h"
#include "UtilityEx.h"

using namespace std;

UPS::Python::PyPluginAdapter::PyPluginAdapter(PyObject* plugin)
{
  _pyObject = plugin;
  Py_INCREF(_pyObject);
}


UPS::Python::PyPluginAdapter::~PyPluginAdapter()
{
  Py_DECREF(_pyObject);
}

const std::wstring UPS::Python::PyPluginAdapter::name()
{
  auto* name = PyObject_CallMethod(_pyObject, "name", NULL);
  wstring result = UtilityEx::pyObject2wstring(name);
  Py_XDECREF(name);
  return result;
}

void UPS::Python::PyPluginAdapter::set(const std::wstring & param)
{
  PyObject_CallMethod(_pyObject, "set", "u#", param.c_str(), param.length());
}

void UPS::Python::PyPluginAdapter::unset(const std::wstring & param)
{
  PyObject_CallMethod(_pyObject, "unset", "u#", param.c_str(), param.length());
}

const std::wstring UPS::Python::PyPluginAdapter::invoke(const std::wstring & param)
{
  auto* obj = PyObject_CallMethod(_pyObject, "invoke", "u#", param.c_str(), param.length());
  auto result = UtilityEx::pyObject2wstring(obj);
  Py_XDECREF(obj);
  return result;
}
