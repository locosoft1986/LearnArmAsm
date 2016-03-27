#!/bin/sh

cmake -G "CodeLite - Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=../toolchain-arm-none-eabi-rpibplus.cmake ./
