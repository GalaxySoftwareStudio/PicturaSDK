#!/bin/sh
# Pictura SDK Clean project

set -e

cd "`dirname "$0"`"

echo --- CLEANING UP SDK PROJECT ---
echo Ignore the error messages if you see any...
echo

rm -rf ./Framework
rm -rf ./Intermediate
rm -rf ./PicturaSDK.xcworkspace
rm -rf ./.vs
rm -f ./Sources/PicturaFramework.vcxproj
rm -f ./Sources/PicturaFramework.vcxproj.filters
rm -rf ./Sources/PicturaFramework.xcodeproj
rm -f ./PicturaSDK.sln
rm -f ./Makefile
rm -f ./Sources/Makefile
