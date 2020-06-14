@echo off
echo --- CLEANING UP SDK PROJECT ---
echo.
pushd %~dp0\
rmdir /Q /S .\Framework
rmdir /Q /S .\Intermediate
rmdir /Q /S .\PicturaSDK.xcworkspace
rmdir /Q /S .\.vs
del .\Sources\PicturaFramework.vcxproj
del .\Sources\PicturaFramework.vcxproj.filters
rmdir /Q /S .\Sources\PicturaFramework.xcodeproj
del .\PicturaSDK.sln
popd