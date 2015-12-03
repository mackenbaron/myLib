// testdump.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <DbgHelp.h>  
#include <eh.h>
#pragma comment(lib, "dbghelp.lib") 

void ExceptionHandler(UINT nSeCode, _EXCEPTION_POINTERS* pExcPointers)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	char szFileName[255];
	GetModuleFileName(NULL, szFileName, 255);

	if( !CreateProcess( /* "../Debug/Tmp.exe", // 你程序的全路径。*/
		szFileName, 
		NULL, // Command line.  
		NULL, // Process handle not inheritable.  
		NULL, // Thread handle not inheritable.  
		FALSE, // Set handle inheritance to FALSE.  
		0, // No creation flags.  
		NULL, // Use parent's environment block.  
		NULL, // Use parent's starting directory.  
		&si, // Pointer to STARTUPINFO structure.
		&pi ) // Pointer to PROCESS_INFORMATION structure.
		)  
	{
		printf( "CreateProcess failed (%d).\n", GetLastError() );
	}

	exit(1);
}

inline BOOL IsDataSectionNeeded(const WCHAR* pModuleName)  
{  
	if(pModuleName == NULL)  
	{  
		return FALSE;  
	}  

	WCHAR szFileName[_MAX_FNAME] = L"";  
	_wsplitpath(pModuleName, NULL, NULL, szFileName, NULL);  

	if(wcsicmp(szFileName, L"ntdll") == 0)  
		return TRUE;  

	return FALSE;  
}  

inline BOOL CALLBACK MiniDumpCallback(PVOID                            pParam,  
	const PMINIDUMP_CALLBACK_INPUT   pInput,  
	PMINIDUMP_CALLBACK_OUTPUT        pOutput)  
{  
	if(pInput == 0 || pOutput == 0)  
		return FALSE;  

	switch(pInput->CallbackType)  
	{  
	case ModuleCallback:  
		if(pOutput->ModuleWriteFlags & ModuleWriteDataSeg)  
			if(!IsDataSectionNeeded(pInput->Module.FullPath))  
				pOutput->ModuleWriteFlags &= (~ModuleWriteDataSeg);  
	case IncludeModuleCallback:  
	case IncludeThreadCallback:  
	case ThreadCallback:  
	case ThreadExCallback:  
		return TRUE;  
	default:;  
	}  

	return FALSE;  
}  

inline void CreateMiniDump(PEXCEPTION_POINTERS pep, LPCTSTR strFileName)  
{  
	HANDLE hFile = CreateFile(strFileName, GENERIC_READ | GENERIC_WRITE,  
		FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);  

	if(hFile != INVALID_HANDLE_VALUE)
	{  
		MINIDUMP_EXCEPTION_INFORMATION mdei;
		mdei.ThreadId           = GetCurrentThreadId();  
		mdei.ExceptionPointers  = pep;  
		mdei.ClientPointers     = FALSE;  

		MINIDUMP_CALLBACK_INFORMATION mci;  
		mci.CallbackRoutine     = (MINIDUMP_CALLBACK_ROUTINE)MiniDumpCallback;  
		mci.CallbackParam       = NULL;  

		::MiniDumpWriteDump(::GetCurrentProcess(), ::GetCurrentProcessId(), hFile, MiniDumpNormal, (pep != NULL) ? &mdei : NULL, NULL, &mci);  

		CloseHandle(hFile);  
	}  
}  


LONG __stdcall MyUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)  
{
	CreateMiniDump(pExceptionInfo, "core.dmp");  

	SetErrorMode(SEM_FAILCRITICALERRORS|SEM_NOGPFAULTERRORBOX);
	_set_se_translator(ExceptionHandler);
	return EXCEPTION_EXECUTE_HANDLER;  
}  

int _tmain(int argc, _TCHAR* argv[])
{
	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);
	int i = 0; 
	//printf("adsf");
	int c = 10/i;
	return 0;
}

