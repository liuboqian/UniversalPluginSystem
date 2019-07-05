// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>



// reference additional headers your program requires here
#ifdef _DEBUG
#pragma comment(lib, "../x64/Debug/PluginManager.Core.lib")
#else
#pragma comment(lib, "../x64/Release/PluginManager.Core.lib")
#endif