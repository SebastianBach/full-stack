#!/bin/bash

echo "build asm program"

LIB_C=$1
TARGET=$2
RUN=$3


echo $LIB_C

# Check the value of X and print "A" or "B" accordingly
if [ "$TARGET" = "release" ]; then

    echo "build release"

    gcc -nostdlib -o temp/program program.s $LIB_C -nostartfiles -no-pie -lc

    if [ "$RUN" = "run" ]; then
        ./temp/program
    fi

elif [ "$TARGET" = "debug" ]; then

    echo "build debug and run gdb"

    gcc -nostdlib -o temp/program program.s $LIB_C -nostartfiles -no-pie  -g -lc

    # r
    # n

    if [ "$RUN" = "run" ]; then
        gdb --args ./temp/program 
    fi

else
    echo "no target given"
fi
