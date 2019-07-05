#include "stdafx.h"
#include "Utility.h"

using namespace std;


std::string UPS::Utility::wstring2string(std::wstring str)
{
  auto buf = wchars2chars(str.c_str());
  string result(buf.get());
  return result;
}

std::wstring UPS::Utility::string2wstring(std::string str)
{
  auto buf = chars2wchars(str.c_str());
  wstring result(buf.get());
  return result;
}

std::shared_ptr<char> UPS::Utility::wchars2chars(const WCHAR * str)
{
  char* buf = new char[lstrlenW(str) + 1];
  if (WideCharToMultiByte(CP_UTF8, 0, str, -1, buf, lstrlenW(str) + 1, NULL, NULL) == 0)
    throw runtime_error("Can't convert wstring to string");
  return shared_ptr<char>(buf, [](char* ptr)->void {delete[] ptr; });
}

std::shared_ptr<WCHAR> UPS::Utility::chars2wchars(const char * str)
{
  WCHAR* buf = new WCHAR[strlen(str) + 1];
  if (MultiByteToWideChar(CP_UTF8, 0, str, -1, buf, strlen(str) + 1) == 0)
    throw runtime_error("Can't convert string to wstring");
  return shared_ptr<WCHAR>(buf, [](WCHAR* ptr)->void {delete[] ptr; });
}