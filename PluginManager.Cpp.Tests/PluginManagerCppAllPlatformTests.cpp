#include "pch.h"
#include <iostream>
#include <string>
#include <Windows.h>

#include "../PluginManager.Core/PluginManagerFactory.h"
#include "../PluginManager.Core/PluginManagerDLL.h"
#include "../PluginSampleCpp/Parameter.h"

using namespace std;
using namespace UPS;

class PluginManagerCppAllPlatformTests
	: public ::testing::Test {
protected:
	PluginManagerCppAllPlatformTests() {
		manager = createPluginManager(true);
	}

	~PluginManagerCppAllPlatformTests() {
		//deletePluginManager(manager);
	}

	void SetUp() override {
		manager->setAllPlatform(true);
		manager->clearParts();
		// Add current dir
		LPWSTR buf = new wchar_t[256];
		GetCurrentDirectory(256, buf);
		LPWSTR curdir = _wcsdup(buf);
		manager->addPart(curdir);

		manager->composeAll();
		parts = manager->getParts();
		pluginNames = manager->getAllPluginNames();
	}

	IPluginManager* manager;
	vector<wstring> parts;
	vector<wstring> pluginNames;
};

TEST_F(PluginManagerCppAllPlatformTests, getPluginNamesTest) {
	auto names = manager->getPluginNames();
	EXPECT_TRUE(names.size(), 3);
}

TEST_F(PluginManagerCppAllPlatformTests, pluginsTest) {
	for (auto name : this->pluginNames) {
		auto plugin = manager->getPlugin(name);
		EXPECT_EQ(plugin->name(), name);
	}
}

TEST_F(PluginManagerCppAllPlatformTests, releaseTest) {
	//manager->getFactory()->releaseAll();
}