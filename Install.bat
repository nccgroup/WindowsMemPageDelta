REM Run this from an elevated command prompt

REM -------------------------------------------
REM This is the installation
REM -------------------------------------------
REM Copy the Eventlog DLL to the Windows directory
copy NCCGroup-WMPD-EvtLog.dll c:\Windows\NCCGroup-WMPD-EvtLog.dll
REM Copy the Main Binary
copy WindowsMemPageDelta.exe c:\Windows\WindowsMemPageDelta.exe

REM Create the service
sc create NCCMemDelta displayname= "NCC Group Memory Delta" binpath= "\"c:\Windows\WindowsMemPageDelta.exe\" -s" start= auto
REM Start the service
net start NCCMemDelta

REM -------------------------------------------
REM This is the Eventlog manifest
REM -------------------------------------------
wevtutil install-manifest SvcEventManifest.man