#!/bin/bash

echo "build asm program"

LIB_C=$1
TARGET=$2
RUN=$3


echo $LIB_C

if [ -d "temp" ]; then
    echo "temp folder exists."
else
    mkdir "temp"
    echo "Folder temp created."
fi

# Check the value of X and print "A" or "B" accordingly
if [ "$TARGET" = "release" ]; then

    echo "build release"

    gcc -o temp/program program.s $LIB_C -nostartfiles -no-pie -lc -lstdc++

    if [ "$RUN" = "run" ]; then
        ./temp/program
    fi

elif [ "$TARGET" = "debug" ]; then

    echo "build debug and run gdb"

    gcc -o temp/program program.s $LIB_C -nostartfiles -no-pie  -g -lc -lstdc++

    # r
    # n

    if [ "$RUN" = "run" ]; then
        gdb --args ./temp/program 
    fi

else
    echo "no target given"
fi
