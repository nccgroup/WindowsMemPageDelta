/*
A Microsoft Windows memory page delta tool

Released as open source by NCC Group Plc - http://www.nccgroup.com/

Developed by Ollie Whitehouse, ollie dot whitehouse at nccgroup dot com

https://github.com/nccgroup/WindowsMemPageDelta

Released under AGPL see LICENSE for more information
*/

// Includes
#include "stdafx.h"

bool	bService = false;

// Globals
HANDLE	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

/// 
int _tmain(int argc, _TCHAR* argv[])
{
	RegisterEvent();

	if (lstrcmpi(argv[1], TEXT("-i")) == 0)
	{
		fwprintf(stdout,L"Installing service\n");
		SvcInstall();
		return 0;
	}
	else if (lstrcmpi(argv[1], TEXT("-c")) == 0)
	{
		fwprintf(stdout, L"Running command line\n");

		// Loop
		while (true) {
			EnumerateProcesses();
			if (bFirstRun == true) bFirstRun = false;
			Sleep(30000);
		}
	}
	else if (lstrcmpi(argv[1], TEXT("-s")) == 0)
	{

		fwprintf(stdout, L"Service\n");

		bService = true;

		WriteEvent(TEXT("Dispatched.."));

		// TO_DO: Add any additional services for the process to this table.
		SERVICE_TABLE_ENTRY DispatchTable[] =
		{
			{ SVCNAME, (LPSERVICE_MAIN_FUNCTION)SvcMain },
			{ NULL, NULL }
		};

		// This call returns when the service has stopped. 
		// The process should simply terminate when the call returns.

		if (!StartServiceCtrlDispatcher(DispatchTable))
		{
			fwprintf(stdout, L"Error doing dispatch\n");
		}

		WriteEvent(TEXT("Shutting down"));
		fwprintf(stdout, L"Finished service\n");

	}

	UnRegisterEvent();
	return 0;
}

