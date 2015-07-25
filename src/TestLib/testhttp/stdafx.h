// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


#include <stdio.h>
#include <tchar.h>

#include <windows.h>
#include <shellapi.h>
#include <Shlwapi.h>
#include <conio.h>        // For _kbhit() on Windows
#include <direct.h>        // For mkdir(path) on Windows
#include "time.h"
#include <stdio.h>
#include <stdlib.h> 
#define snprintf sprintf_s    // Visual Studio on Windows comes with sprintf_s() instead of snprintf()

#pragma comment(lib,"Shlwapi.lib")
#pragma comment(lib, "DbgHelp.lib")

#include <string.h>  
#include <iostream>  
#include <fstream>  

#include "curl/curl.h"
#include "htmlcxx/html/ParserDom.h"  
#include <stdlib.h>  
#include <stdio.h>  
#include "htmlcxx/html/utils.h"  
using namespace std;
using namespace htmlcxx;

// TODO: reference additional headers your program requires here
