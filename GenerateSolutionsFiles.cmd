@echo off
pushd %~dp0\
call .\Vendor\premake\premake.exe --verbose --file=./generate-sdk.lua vs2019
popd
timeout 1 > nul