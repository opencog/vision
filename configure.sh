#!/bin/bash
set -ex

cmake -B build/ -S . \
    -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=1

cp build/compile_commands.json .
