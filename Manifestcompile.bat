@echo off
echo Compiling manifest
mc.exe SvcEventManifest.man
echo Resouring manifest
rc.exe SvcEventManifest.rc
echo Linking manifest
link.exe  /dll /noentry /machine:x64 SvcEventManifest.res /OUT:NCCGroup-WMPD-EvtLog.dll
echo Finished manifest