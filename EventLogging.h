/*
A Microsoft Windows memory page delta tool

Released as open source by NCC Group Plc - http://www.nccgroup.com/

Developed by Ollie Whitehouse, ollie dot whitehouse at nccgroup dot com

https://github.com/nccgroup/WindowsMemPageDelta

Released under AGPL see LICENSE for more information
*/

#pragma once
#include "stdafx.h"

void RegisterEvent();
void WriteEvent(LPWSTR strMessage);
void WriteTotal(LPWSTR strMessage);
void UnRegisterEvent();
