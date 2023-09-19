#!/bin/bash
libs=-luser32
warnings="-Wno-writable-strings -Wno-format-security"

clang src/main.cpp -g -o celestialHeights.exe $libs $warnings