#include "pch.h"
#include <iostream>
#include "..\PluginManager.Core\Utility.h"
using namespace std;
using namespace UPS;

TEST(UtilityTest, ws2sTest) {
	wstring s1 = L"This is a test string";
	string s2 = Utility::wstring2string(s1);
	EXPECT_EQ(s2, "This is a test string");
}

TEST(UtilityTest, s2wsTest) {
	string s1 = "A long string";
	wstring s2 = Utility::string2wstring(s1);
	EXPECT_EQ(s2, L"A long string");
}

TEST(UtilityTest, wc2cTest) {
	WCHAR s1[] = L"abcd efgh ";
	auto s2 = Utility::wchars2chars(s1);
	EXPECT_STREQ(s2.get(), "abcd efgh ");
}

TEST(UtilityTest, c2wcTest) {
	char s1[] = "agheghsetdkas";
	auto s2 = Utility::chars2wchars(s1);
	EXPECT_EQ(lstrcmpW(s2.get(), L"agheghsetdkas"), 0);
}