#include "stdafx.h"
#include "UtilityEx.h"
#include "../PluginManager.Core/Utility.h"

using namespace std;

std::string UPS::Python::UtilityEx::pyObject2string(PyObject * object)
{
  if (object == nullptr)
    return string();
  auto* chars = PyUnicode_AsUTF8(object);
  string str(chars);
  return str;
}

std::wstring UPS::Python::UtilityEx::pyObject2wstring(PyObject * object)
{
  if (object == nullptr)
    return wstring();
  return Utility::string2wstring(pyObject2string(object));
}

std::shared_ptr<PyObject> UPS::Python::UtilityEx::string2pyObject(std::string str)
{
  auto* object = PyUnicode_FromStringAndSize(str.c_str(), str.length());
  return shared_ptr<PyObject>(object, [](PyObject* obj)->void {Py_XDECREF(obj); });
}

std::shared_ptr<PyObject> UPS::Python::UtilityEx::wstring2pyObject(std::wstring str)
{
  return string2pyObject(Utility::wstring2string(str));
}
