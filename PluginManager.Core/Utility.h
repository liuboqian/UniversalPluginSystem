#pragma once
#include <string>
#include <iostream>
#include "IPlugin.h"

namespace UPS {
	static class DLL Utility
	{
	public:
		static std::string wstring2string(std::wstring str);
		static std::wstring string2wstring(std::string str);
		static std::shared_ptr<char> wchars2chars(const WCHAR* str);
		static std::shared_ptr<WCHAR> chars2wchars(const char* str);
	};
}

