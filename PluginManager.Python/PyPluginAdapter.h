#pragma once
#include "../include/python/include/Python.h"
#include "../PluginManager.Core/IPlugin.h"

#ifdef PLUGINMANAGERPYTHON_EXPORTS
#define DLL __declspec(dllexport)
#define DLLAPI EXTERN_C __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#define DLLAPI EXTERN_C __declspec(dllimport)
#endif

namespace UPS {
  namespace Python {
    class PyPluginAdapter : public IPlugin
    {
    public:
      PyPluginAdapter(PyObject* plugin);
      ~PyPluginAdapter();
      // Inherited via IPlugin
      virtual const std::wstring name() override;
      virtual void set(const std::wstring & param) override;
      virtual void unset(const std::wstring & param) override;
      virtual const std::wstring invoke(const std::wstring & param) override;
      
    private:
      PyObject* _pyObject;
    };
  }
}


