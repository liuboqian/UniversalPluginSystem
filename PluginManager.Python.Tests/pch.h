//
// pch.h
// Header for standard system include files.
//

#pragma once

#include "gtest/gtest.h"

#include <Windows.h>
#ifdef _DEBUG
#pragma comment(lib, "../include/python/amd64/python36_d.lib")
#else
#pragma comment(lib, "../include/python/amd64/python36.lib")
#endif