#!/bin/sh
# Pictura SDK Xcode project generation command

set -e

cd "`dirname "$0"`"

if [ "$(uname)" = "Darwin" ]; then
    ./Vendor/premake/premake_osx --verbose --file=./generate-sdk.lua xcode4
else
    # assume (GNU/)Linux
    ./Vendor/premake/premake --verbose --file=./generate-sdk.lua gmake2
fi

sleep 3 &> /dev/null
