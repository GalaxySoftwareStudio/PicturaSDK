#!/bin/sh
# Pictura SDK Xcode project generation command

set -e

cd "`dirname "$0"`"

if [ "$(uname)" = "Darwin" ]; then
    ./Vendor/premake/premake_osx --os=macosx --verbose --file=./generate-sdk.lua xcode4
else
    # assume (GNU/)Linux
    ./Vendor/premake/premake --os=linux --verbose --file=./generate-sdk.lua gmake2
fi

sleep 1 &> /dev/null
