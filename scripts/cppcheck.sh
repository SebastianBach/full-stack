cd ..

mkdir build
cd build

cmake       -DCMAKE_BUILD_TYPE=Release\
            -DCMAKE_EXPORT_COMPILE_COMMANDS=ON\
            -DADD_BASIC_TOOLS=ON\
            -DADD_SDK=ON\
            -DADD_C_LIB=ON\
            -DADD_DYNAMIC_LIB=ON\
            -DADD_PYTHON_MODULE=ON\
            -DADD_QT_APP=ON\
            -DADD_RUST_APP=ON\
            -DADD_PY_DOCS=ON\
            -DADD_LIB_DOCS=ON\
            -DADD_SCRIPT_TOOLS=ON\
            -DADD_ASSEMBLY_PROGRAM=ON ..

cmake --build . -j --config Release


cppcheck --project=compile_commands.json --cppcheck-build-dir=./temp/cppcheck
