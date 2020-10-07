Windows Executable Memory Page Delta Reporter
======================

A Windows Service to performantly produce telemetry on new or modified Windows memory pages that are now executable every 30 seconds.

Released as open source by NCC Group Plc - http://www.nccgroup.com/

Developed by Ollie Whitehouse, ollie dot whitehouse at nccgroup dot com

https://github.com/nccgroup/WindowsMemPageDelta

Released under AGPL see LICENSE for more information

Blog
-------------
https://research.nccgroup.com/2020/10/03/tool-windows-executable-memory-page-delta-reporter/

Hypothesis
-------------
Collect enough telemetry from a Windows host or an entire estate on which processes create and change memory so its executable along with their size and you’ll be able to spot the anomalies. These anomalies may be malicious activity.

Compatibility
-------------
Only Windows 10 is supported / tested

What it does
-------------
Simply:
* rapidly scans Windows processes every 30 seconds
* enumerates their memory pages, protection and state
* identifies differences - noting those that are now executable that were not on the previous run

Performant in that
* consumes a constant of about 95MB of RAM
* takes about 8 seconds to run

History
-------------
Part of this code is based on a project I wrote back in 2014 called WindowsPatchDetector - https://github.com/olliencc/WindowsPatchDetector . This project detected changes in the .text section compared to that on disk.

To do
-------------
- [X] Add eventlog output
- [X] Make a Windows service

Command Line Options
-------------

Run it as a console app
```
WindowsMemPageDelta.exe -c
```

Run it as a Windows service
```
WindowsMemPageDelta.exe -s
```

Installation
-------------
The below is a batch file which can be used to install the service.

```
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
```

Logs are in Event Logging
-------------
There are two buckets
- Individual executable page deltas - to detect specific anomalies
- Totals of executable memory per process - to aid longitudal monitoring and variance detection

Individual deltas:
![Eventvwr Example for Deltas](https://raw.githubusercontent.com/nccgroup/WindowsMemPageDelta/master/images/Eventvwr.PNG)

Totals:
![Eventvwr Example for Totals](https://raw.githubusercontent.com/nccgroup/WindowsMemPageDelta/master/images/Eventvwr2.PNG)

Output schema
-------------
The schema for New delta events is:
```
TYPE,PID,Process Name,Address,Size,Protection
```

Example
```
New,32068,ServiceHub.DataWarehouseHost.exe,7ffd5b9d0000,53248,XRW....
New,32068,ServiceHub.DataWarehouseHost.exe,7ffd93f51000,69632,XR....
New,32068,ServiceHub.DataWarehouseHost.exe,7ffd97241000,1015808,XR....
New,12692,ScriptedSandbox64.exe,1e247250000,20480,X.....
New,12692,ScriptedSandbox64.exe,1e2475f0000,4096,X.....
New,12692,ScriptedSandbox64.exe,1e247770000,32768,X.....
New,12692,ScriptedSandbox64.exe,1e2477b0000,12288,X.....
New,12692,ScriptedSandbox64.exe,1e2477f0000,16384,X.....
New,12692,ScriptedSandbox64.exe,1e247af0000,40960,X.....
...
```

The schema for Change delta events is:

```
TYPE,PID,Process Name,Address,Size,Protection,Previous Protection
```

```
Changed,16008,Teams.exe,cc86df04000,503808,XR....,.RW....
Changed,16008,Teams.exe,cc86e004000,86016,XR....,.RW....
Changed,16008,Teams.exe,cc86e084000,86016,XR....,.RW....
Changed,16008,Teams.exe,cc86e104000,86016,XR....,.RW....
Changed,16008,Teams.exe,cc86e284000,503808,XR....,.RW....
Changed,16008,Teams.exe,cc86e604000,503808,XR....,.RW....
Changed,16008,Teams.exe,cc86e984000,503808,XR....,.RW....
Changed,16008,Teams.exe,cc86ea04000,503808,XR....,.RW....
Changed,16008,Teams.exe,cc86ec84000,503808,XR....,.RW....
```

The schema for Total events is:
```
TYPE,PID,Process Name,Total Executable Memory Bytes
```

```
Total,36904,chrome.exe,451309568
Total,38772,chrome.exe,324202496
Total,9508,conhost.exe,95203328
Total,38808,mspdbsrv.exe,31637504
Total,5292,SearchProtocolHost.exe,434233344
Total,31036,chrome.exe,268713984
Total,25940,chrome.exe,262905856
Total,1184,Teams.exe,259481600
Total,36984,conhost.exe,154443776
```