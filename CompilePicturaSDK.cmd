@echo off
echo Compiling Pictura SDK...
"C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\amd64\msbuild.exe" -noLogo -maxCpuCount PicturaSDK.sln
timeout 2 > nul