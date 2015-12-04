// testcrashrpt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <assert.h>
#include <process.h>
#include <iostream>
#include "CrashRpt.h" // Include CrashRpt header

BOOL WINAPI CrashCallback(LPVOID lpvState)
{
	UNREFERENCED_PARAMETER(lpvState);

	// Crash happened!

	return TRUE;
}

int _tmain(int argc, _TCHAR* argv[])
{
	CR_INSTALL_INFO info;
	memset(&info, 0, sizeof(CR_INSTALL_INFO));
	info.cb = sizeof(CR_INSTALL_INFO);  
	info.pszAppName = _T("WTLDemo"); // Define application name.
	info.pszAppVersion = _T("1.3.1");     // Define application version.
	info.pszEmailSubject = _T("WTLDemo Error Report"); // Define subject for email.
	info.pszEmailTo = _T("test@hotmail.com");   // Define E-mail recipient address.  
	//info.pszSmtpProxy = _T("127.0.0.1");  // Use SMTP proxy.
	//info.pszSmtpLogin = _T("test");      // SMTP Login
	//info.pszSmtpPassword = _T("test");       // SMTP Password
	info.pszUrl = _T("http://192.168.0.26:9000/Operation/CrashLog"); // URL for sending reports over HTTP.				
	//info.pfnCrashCallback = CrashCallback; // Define crash callback function.   
	// Define delivery methods priorities. 
	info.uPriorities[CR_HTTP] = 3;         // Use HTTP the first.
	info.uPriorities[CR_SMTP] = 2;         // Use SMTP the second.
	info.uPriorities[CR_SMAPI] = 1;        // Use Simple MAPI the last.  
	info.dwFlags = 0;                    
	info.dwFlags |= CR_INST_ALL_POSSIBLE_HANDLERS; // Install all available exception handlers.    
	//info.dwFlags |= CR_INST_APP_RESTART;            // Restart the application on crash.  
	//info.dwFlags |= CR_INST_NO_MINIDUMP;          // Do not include minidump.
	//info.dwFlags |= CR_INST_NO_GUI;               // Don't display GUI.
	//info.dwFlags |= CR_INST_DONT_SEND_REPORT;     // Don't send report immediately, just queue for later delivery.
	//info.dwFlags |= CR_INST_STORE_ZIP_ARCHIVES;   // Store ZIP archives along with uncompressed files (to be used with CR_INST_DONT_SEND_REPORT)
	//info.dwFlags |= CR_INST_SEND_MANDATORY;         // Remove "Close" and "Other actions..." buttons from Error Report dialog.
	//info.dwFlags |= CR_INST_SHOW_ADDITIONAL_INFO_FIELDS; //!< Make "Your E-mail" and "Describe what you were doing when the problem occurred" fields of Error Report dialog always visible.
	info.dwFlags |= CR_INST_ALLOW_ATTACH_MORE_FILES; //!< Adds an ability for user to attach more files to crash report by clicking "Attach More File(s)" item from context menu of Error Report Details dialog.
	//info.dwFlags |= CR_INST_SEND_QUEUED_REPORTS;    // Send reports that were failed to send recently.	
	//info.dwFlags |= CR_INST_AUTO_THREAD_HANDLERS; 
	info.pszDebugHelpDLL = NULL;                    // Search for dbghelp.dll using default search sequence.
	info.uMiniDumpType = MiniDumpNormal;            // Define minidump size.
	// Define privacy policy URL.
	//info.pszPrivacyPolicyURL = _T("http://code.google.com/p/crashrpt/wiki/PrivacyPolicyTemplate");
	info.pszErrorReportSaveDir = NULL;       // Save error reports to the default location.
	info.pszRestartCmdLine = _T("/restart"); // Command line for automatic app restart.
	//info.pszLangFilePath = _T("D:\\");       // Specify custom dir or filename for language file.
	//info.pszCustomSenderIcon = _T("C:\\WINDOWS\\System32\\user32.dll, 1"); // Specify custom icon for CrashRpt dialogs.

	// Install crash handlers.
	CrAutoInstallHelper cr_install_helper(&info);
	if(cr_install_helper.m_nInstallStatus!=0)
	{
		TCHAR buff[256];
		crGetLastErrorMsg(buff, 256);
		MessageBox(NULL, buff, _T("crInstall error"), MB_OK);
		return FALSE;
	}
	assert(cr_install_helper.m_nInstallStatus==0); 

	std::wstring sLogFile =L".\\*.log";
	std::wstring sIniFile = L".\\dummy.ini";

	int nResult = crAddFile2(sLogFile.c_str(), NULL, _T("Dummy Log File"), CR_AF_MAKE_FILE_COPY|CR_AF_ALLOW_DELETE);
	assert(nResult==0);

	nResult = crAddFile2(sIniFile.c_str(), NULL, _T("Dummy INI File"), 0);
	assert(nResult==0);

	nResult = crAddScreenshot2(CR_AS_PROCESS_WINDOWS|CR_AS_USE_JPEG_FORMAT|CR_AS_ALLOW_DELETE, 10);
	//nResult = crAddScreenshot(CR_AS_MAIN_WINDOW);
	assert(nResult==0);

	nResult = crAddProperty(_T("AnExampleProperty"),_T("Property value"));
	assert(nResult==0);

	nResult = crAddProperty(_T("VideoCard"),_T("nVidia GeForce 9800"));
	assert(nResult==0);

	nResult = crAddProperty(_T("HDDSerialNumber"),_T("1234512345098765"));
	assert(nResult==0);

	nResult = crAddProperty(_T("MACAddress"),_T("11.11.11.11"));
	assert(nResult==0);

	nResult = crAddProperty(_T("UserName"),_T("TheUserName"));
	assert(nResult==0);

	nResult = crAddRegKey(_T("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer"), _T("regkey.xml"), CR_AR_ALLOW_DELETE);
	assert(nResult==0);

	nResult = crAddRegKey(_T("HKEY_LOCAL_MACHINE\\Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings"), _T("regkey.xml"), CR_AR_ALLOW_DELETE);
	assert(nResult==0);

	printf("Press Enter to simulate a null pointer exception or any other key to exit...\n");
	int n = _getch();
	if(n==13)
	{
		int *p = 0;
		*p = 0; // Access violation
	}

	int nUninstRes = crUninstall(); // Uninstall exception handlers
	assert(nUninstRes==0);
	return 0;
}

