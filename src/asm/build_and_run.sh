#!/bin/bash

echo ""

SOURCE_FILE=$1
BINARY=$2
LIB_TITLE_CASE=$3
TARGET=$4
BUILD_FOLDER=$5
RUN=$6
TEST_ARG=$7

echo 'SOURCE_FILE:    '$SOURCE_FILE
echo 'BINARY:         '$BINARY
echo 'LIB_TITLE_CASE: '$LIB_TITLE_CASE
echo 'TARGET:         '$TARGET
echo 'BUILD_FOLDER:   '$BUILD_FOLDER
echo 'RUN:            '$RUN
echo 'TEST_ARG:       '$TEST_ARG
echo ""


if [ -d $BUILD_FOLDER ]; then
    echo "build folder exists."
else
    mkdir $BUILD_FOLDER
    echo "build folder created."
fi


if [ "$TARGET" = "Release" ]; then

    echo "build release"
    echo ""

    gcc  -o $BUILD_FOLDER/$BINARY $SOURCE_FILE $LIB_TITLE_CASE -m64 -lc -O2 -nostartfiles
    strip --strip-all $BUILD_FOLDER/$BINARY

    if [ "$RUN" = "run" ]; then
        $BUILD_FOLDER/$BINARY "$TEST_ARG"
        return_code=$?
        echo ""
        echo "Return code: $return_code"
    fi

elif [ "$TARGET" = "Debug" ]; then

    echo "build debug and run gdb"

    gcc -o $BUILD_FOLDER/$BINARY $SOURCE_FILE $LIB_TITLE_CASE -nostartfiles -no-pie  -g -lc -lstdc++

    if [ "$RUN" = "run" ]; then
        gdb --args $BUILD_FOLDER/$BINARY "$TEST_ARG"
    fi

else
    echo "no target given"
fi
