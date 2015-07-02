// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#if defined WIN32 || defined _WIN32
#include <windows.h>
#include <shellapi.h>
#include <Shlwapi.h>
#include <conio.h>        // For _kbhit() on Windows
#include <direct.h>        // For mkdir(path) on Windows
#include "time.h"
#include <stdio.h>
#include <stdlib.h> 
#define snprintf sprintf_s    // Visual Studio on Windows comes with sprintf_s() instead of snprintf()
#else
#include <stdio.h>        // For getchar() on Linux
#include <termios.h>    // For kbhit() on Linux
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>    // For mkdir(path, options) on Linux
#endif

// TODO: reference additional headers your program requires here
#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#ifdef _WIN32
#pragma comment(lib,"Shlwapi.lib")
#pragma comment(lib, "DbgHelp.lib")
#endif