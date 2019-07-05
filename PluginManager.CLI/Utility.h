#pragma once
#include <iostream>

namespace UPS {
	namespace CLI {
		static class UtilityEx
		{
		public:
			static System::String^ wstring2CSString(std::wstring str);
			static std::wstring CSString2wstring(System::String^ str);
		};
	}
}

