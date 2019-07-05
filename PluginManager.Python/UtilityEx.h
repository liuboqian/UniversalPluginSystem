#pragma once
#include <iostream>

#include "../include/python/include/Python.h"

#ifdef PLUGINMANAGERPYTHON_EXPORTS
#define DLL __declspec(dllexport)
#define DLLAPI EXTERN_C __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#define DLLAPI EXTERN_C __declspec(dllimport)
#endif

namespace UPS {
  namespace Python {
    static class DLL UtilityEx
    {
    public:
      static std::string pyObject2string(PyObject* object);
      static std::wstring pyObject2wstring(PyObject* object);
      static std::shared_ptr<PyObject> string2pyObject(std::string str);
      static std::shared_ptr<PyObject> wstring2pyObject(std::wstring str);
    };

  }
}

