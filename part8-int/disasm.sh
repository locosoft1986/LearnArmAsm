#!/bin/sh

arm-none-eabi-objdump -D ./main.elf > ./kernel.asm
arm-none-eabi-nm ./main.elf > ./kernel.nm