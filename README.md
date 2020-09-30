Windows Executable Memory Page Delta Reporter
======================

A tool to performantly produce telemetry on new or modified Windows memory pages that are now executable every 30 seconds.

Released as open source by NCC Group Plc - http://www.nccgroup.com/

Developed by Ollie Whitehouse, ollie dot whitehouse at nccgroup dot com

https://github.com/nccgroup/WindowsMemPageDelta

Released under AGPL see LICENSE for more information

Hypothesis
-------------
Collect enough telemetry from a Windows host/estate about which processes create and change memory as/to executeable along with their size and you'll be able to spot the anonamlies. These anomalies may be malicious activity.

What it does
-------------
Simply:
* rapidly scans Windows processes every 30 seconds
* enumerates their memory pages, protection and state
* identifies differences - noting those that are now executable that were not on the previous run

Performant in that
* consumes a constant of about 95MB of RAM
* takes about 8 seconds to run

Why? Catch bad actors doing process injection.

To do
-------------
- [ ] Add eventlog output
- [ ] Make a Windows service
- [ ] Registry for configuration


Output
-------------
The schema for new events is:
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

The schema for change events is:

```
TYPE,PID,Process Name,Address,Size,Protection,Previous Protection
```

```
...
```
