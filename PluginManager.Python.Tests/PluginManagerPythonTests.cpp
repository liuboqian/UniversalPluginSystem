#include "pch.h"
#include <filesystem>
#include "../PluginManager.Core/IPluginManager.h"
#include "../PluginManager.Core/PluginManagerDLL.h"
#include "../PluginSampleCpp/Parameter.h"

using namespace std;
using namespace UPS;

class PluginManagerPythonTest
  : public ::testing::Test {

protected:
  PluginManagerPythonTest() {
    manager = createPluginManager(false);
  }

  void SetUp() override {
    // Add dir
    LPWSTR buf = new wchar_t[256];
    GetCurrentDirectory(256, buf);
    LPWSTR curdir = _wcsdup(buf);
    manager->addPart(curdir);
    wstring dir = curdir;
    auto pos = dir.rfind(L"\\", dir.length() - 1);
    dir = dir.substr(0, pos);
    pos = dir.rfind(L"\\");
    dir = dir.substr(0, pos);
    dir += L"\\PluginSamplePython\\";

    manager->addPart(dir);
    manager->composeAll();
  }

  IPluginManager* manager;
};

TEST_F(PluginManagerPythonTest, PluginNamesTests) {
  auto names = manager->getAllPluginNames();
  EXPECT_EQ(names.size(), 1);
}

TEST_F(PluginManagerPythonTest, PluginTests) {
  auto plugin = manager->getPlugin(L"PowerCalculator");
  EXPECT_EQ(plugin->name(), L"PowerCalculator");

  Parameter p;
  p.setA(2);
  p.setB(3);
  auto retval = plugin->invoke(p.serialize());
  Result result;
  result.deserialize(retval);
  EXPECT_EQ(result.getResult(), 8);
}