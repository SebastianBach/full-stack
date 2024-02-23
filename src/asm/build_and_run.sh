#!/bin/bash

echo "build asm program"

LIB_C=$1
TARGET=$2
BUILD_FOLDER=$3
RUN=$4


echo $LIB_C

if [ -d $BUILD_FOLDER ]; then
    echo "build folder exists."
else
    mkdir $BUILD_FOLDER
    echo "build folder created."
fi

# Check the value of X and print "A" or "B" accordingly
if [ "$TARGET" = "Release" ]; then

    echo "build release"

    gcc -o $BUILD_FOLDER/program program.s $LIB_C -nostartfiles -no-pie -lc
    
    if [ "$RUN" = "run" ]; then
        $BUILD_FOLDER/program
    fi

elif [ "$TARGET" = "Debug" ]; then

    echo "build debug and run gdb"

    gcc -o $BUILD_FOLDER/program program.s $LIB_C -nostartfiles -no-pie  -g -lc -lstdc++

    # r
    # n

    if [ "$RUN" = "run" ]; then
        gdb --args $BUILD_FOLDER/program 
    fi

else
    echo "no target given"
fi
