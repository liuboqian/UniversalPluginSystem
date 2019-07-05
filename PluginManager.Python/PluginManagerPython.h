#pragma once
#include <set>
#include <unordered_map>
#include "../PluginManager.Core/PluginManagerBase.h"
#include "PyPluginAdapter.h"

namespace UPS {
  namespace Python {
    class PluginManagerPython
      : public PluginManagerBase
    {
    public:
      static PluginManagerPython* createManager(bool allplatform);
      static void deleteManager(PluginManagerPython* manager);

      // Inherited via PluginManagerBase
      virtual void setAllPlatform(bool allplatform) override;
      virtual void compose() override;
      virtual void releasePlugins() override;
      virtual std::vector<std::wstring> getPluginNames() const override;
      virtual std::shared_ptr<IPlugin> getPluginInternal(std::wstring name) const override;

    private:
      PluginManagerPython(bool allplatform);
      ~PluginManagerPython();
      void loadPyFile(const WCHAR* filepath);

      std::unordered_map<std::wstring, std::shared_ptr<PyObject>> _modules;
    };
  }
}
