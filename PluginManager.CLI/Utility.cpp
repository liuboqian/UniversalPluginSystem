#include "stdafx.h"
#include "Utility.h"

using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;

System::String ^ UPS::CLI::UtilityEx::wstring2CSString(std::wstring str)
{
	WCHAR* ptr = const_cast<WCHAR*>(str.c_str());  // could be error-prone
	return Marshal::PtrToStringAuto(IntPtr(ptr), str.length());
}

wstring UPS::CLI::UtilityEx::CSString2wstring(System::String ^ str)
{
	IntPtr ptr = Marshal::StringToHGlobalUni(str);
	LPCTSTR _name = static_cast<LPCTSTR>(ptr.ToPointer());
	return wstring(_name);
}
