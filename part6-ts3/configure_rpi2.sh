#!/bin/sh

cmake -G "CodeLite - Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=../toolchain-arm-none-eabi-rpi2.cmake ./
