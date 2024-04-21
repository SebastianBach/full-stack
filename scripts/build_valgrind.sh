cd ..

mkdir build
cd build
cmake           -DCMAKE_BUILD_TYPE=Debug\
                -DBUILD_VALGRIND=ON\
                -DADD_BASIC_TOOLS=ON\
                -DADD_SDK=ON\
                -DADD_C_LIB=ON\
                -DADD_DYNAMIC_LIB=ON\
                -DADD_QT_APP=ON\
                -DADD_RUST_APP=ON\
                -DADD_SCRIPT_TOOLS=ON\
                -DADD_ASSEMBLY_PROGRAM=ON ..

cmake --build .
ctest -T memcheck 

cd ./Testing/Temporary/

for file in MemoryChecker.*.log; do
    if grep -q "ERROR SUMMARY" "$file"; then
        if ! grep -q "ERROR SUMMARY: 0 errors from 0 contexts" "$file"; then
            echo "File: $file contains errors"
            cat "$file"
        fi
    fi
done
