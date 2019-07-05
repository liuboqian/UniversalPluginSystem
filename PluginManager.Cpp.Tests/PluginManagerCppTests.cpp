#include "pch.h"
#include <iostream>
#include <string>
#include <Windows.h>

#include "../PluginManager.Core/PluginManagerDLL.h"
#include "../PluginSampleCpp/Parameter.h"

using namespace std;
using namespace UPS;

class PluginManagerCppTests 
	: public ::testing::Test {
protected:
	PluginManagerCppTests() {
		manager = createPluginManager(false);
	}

	~PluginManagerCppTests() {
		deletePluginManager(manager);
	}

	void SetUp() override {
		manager->setAllPlatform(false);
		manager->clearParts();
		// Add current dir
		LPWSTR buf = new wchar_t[256];
		GetCurrentDirectory(256, buf);
		LPWSTR curdir = _wcsdup(buf);
		manager->addPart(curdir);

		manager->compose();
		parts = manager->getParts();
		pluginNames = manager->getPluginNames();
	}

	IPluginManager* manager;
	vector<wstring> parts;
	vector<wstring> pluginNames;
};

TEST_F(PluginManagerCppTests, getPluginNamesTest) {
	pluginNames = manager->getPluginNames();
	EXPECT_EQ(pluginNames.size(), 1);
}

TEST_F(PluginManagerCppTests, getPartsTest) {
	parts = manager->getParts();
	EXPECT_EQ(parts.size(), 1);
}

TEST_F(PluginManagerCppTests, addPartTest) {
	EXPECT_EQ(parts.size(), 1);
	manager->addPart(L"test");
	parts = manager->getParts();
	EXPECT_EQ(parts.size(), 2);
	manager->addPart(L"test");
	parts = manager->getParts();
	EXPECT_EQ(parts.size(), 2);
}

TEST_F(PluginManagerCppTests, removePartTest) {
	manager->addPart(L"test");
	parts = manager->getParts();
	EXPECT_EQ(parts.size(), 2);
	manager->removePart(L"test");
	parts = manager->getParts();
	EXPECT_EQ(parts.size(), 1);
	manager->removePart(L"test");
	parts = manager->getParts();
	EXPECT_EQ(parts.size(), 1);
}

TEST_F(PluginManagerCppTests, clearPartsTest) {
	manager->clearParts();
	parts = manager->getParts();
	EXPECT_EQ(parts.size(), 0);
}

TEST_F(PluginManagerCppTests, composeTest) {
	manager->clearParts();
	parts = manager->getParts();
	EXPECT_EQ(parts.size(), 0);
	// Add current dir
	LPWSTR buf = new wchar_t[256];
	GetCurrentDirectory(256, buf);
	LPWSTR curdir = _wcsdup(buf);
	manager->addPart(curdir);

	manager->compose();
	parts = manager->getParts();
	EXPECT_EQ(manager->getPluginNames().size(), 1);
}

TEST_F(PluginManagerCppTests, releaseAllPluginsTest) {
	manager->releasePlugins();
	//EXPECT_ANY_THROW(p->Name());
	EXPECT_EQ(manager->getPluginNames().size(), 0);
}

TEST_F(PluginManagerCppTests, PluginSampleTest) {
	auto sample = manager->getPlugin(pluginNames[0]);
	EXPECT_EQ(sample->name(), L"DivideCalculator");
	Parameter* p = new Parameter();
	p->setA(3);
	p->setB(6);
	auto result = sample->invoke(p->serialize());
	Result* resObj = new Result();
	resObj->deserialize(result);
	EXPECT_EQ(resObj->getResult(), 0.5);
}