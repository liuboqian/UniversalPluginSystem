#include "pch.h"
#include "../PluginManager.Python/UtilityEx.h"

using namespace std;
using namespace UPS::Python;

class UtilityPythonTests
  : public ::testing::Test {
protected:
  UtilityPythonTests() {
  }

  void SetUp() override {
    Py_Initialize();
  }
};

TEST_F(UtilityPythonTests, pyObject2string) {
  string script = "a='test'";
  PyRun_SimpleString(script.c_str());
  auto* main = PyImport_AddModule("__main__");
  auto* obj = PyObject_GetAttrString(main, "a");
  auto result = UtilityEx::pyObject2string(obj);
  EXPECT_EQ(result, "test");
}

TEST_F(UtilityPythonTests, pyObject2wstring) {
  string script = "a='test'";
  PyRun_SimpleString(script.c_str());
  auto* main = PyImport_AddModule("__main__");
  auto* obj = PyObject_GetAttrString(main, "a");
  auto result = UtilityEx::pyObject2wstring(obj);
  EXPECT_EQ(result, L"test");
}

TEST_F(UtilityPythonTests, string2pyObject) {
  string script = "a='test'";
  PyRun_SimpleString(script.c_str());
  auto* main = PyImport_AddModule("__main__");
  auto* obj = PyObject_GetAttrString(main, "a");
  auto result = UtilityEx::string2pyObject("test");
  auto result2 = UtilityEx::string2pyObject("test2");
  EXPECT_EQ(PyUnicode_Compare(obj, result.get()), 0);
  EXPECT_TRUE(PyUnicode_Compare(obj, result2.get()) != 0);
}

TEST_F(UtilityPythonTests, wstring2pyObject) {
  string script = "a='test'";
  PyRun_SimpleString(script.c_str());
  auto* main = PyImport_AddModule("__main__");
  auto* obj = PyObject_GetAttrString(main, "a");
  auto result = UtilityEx::wstring2pyObject(L"test");
  auto result2 = UtilityEx::wstring2pyObject(L"test2");
  EXPECT_EQ(PyUnicode_Compare(obj, result.get()), 0);
  EXPECT_TRUE(PyUnicode_Compare(obj, result2.get()) != 0);
}