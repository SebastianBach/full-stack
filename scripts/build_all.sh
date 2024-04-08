echo build all

trap 'echo "Error: Command failed"; exit 1' ERR

cd ..

if [ ! -d "build" ]; then
    echo "make build folder"
    mkdir build
fi

cd build

cmake -DCMAKE_BUILD_TYPE=Release    -DADD_BASIC_TOOLS=ON\
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
ctest -C Release  -VV
cmake --install .