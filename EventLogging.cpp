/*
A Microsoft Windows memory page delta tool

Released as open source by NCC Group Plc - http://www.nccgroup.com/

Developed by Ollie Whitehouse, ollie dot whitehouse at nccgroup dot com

https://github.com/nccgroup/WindowsMemPageDelta

Released under AGPL see LICENSE for more information
*/

// https://www.developer.com/net/cplus/article.php/3624581/Programming-the-Windows-Vista-Event-Log.htm
// https://kallanreed.wordpress.com/2016/05/28/creating-an-etw-provider-step-by-step/

#include "stdafx.h"

//first step - register the event
REGHANDLE hPub = NULL;

void RegisterEvent() {
	ULONG res = EventRegister(&NCCGROUP_MEMPAGEDELTA_PUBLISHER, NULL, NULL, &hPub);
	if (ERROR_SUCCESS != res) {
		_tprintf(_T("Could not register event\n"));
	}
}

void WriteEvent(LPWSTR strMessage) {

	EVENT_DATA_DESCRIPTOR opEventDesc;
	
	EventDataDescCreate(&opEventDesc, strMessage, ((ULONG)wcslen(strMessage) + 1) * sizeof(WCHAR));

	ULONG res = EventWrite(hPub, &DNP_OP_EVENT, 1, &opEventDesc);
	if (ERROR_SUCCESS != res) {
		_tprintf(_T("Could not raise operational event  Error = %i\n"), res);
	}
}

void UnRegisterEvent() {
	EventUnregister(hPub);
}


