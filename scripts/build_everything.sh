trap 'echo "Error: Command failed"; exit 1' ERR

cd ..

if [ ! -d "build" ]; then
    echo "make build folder"
    mkdir build
fi

cd build
cmake -DADD_PYTHON_MODULE=ON -DADD_QT_APP=ON ..
cmake --build . -j --config Release
ctest -C Release  -VV
cmake --install .

# test lib example project
cd lib_example_build
cmake  ../product/lib/example
cmake --build . --config Release
ctest -C Release  -VV
cd ..
cd ..

cd ..
python -m unittest discover src/test_py
doxygen build/doxyfile
docker build --tag title-case-web .
conan export-pkg . text_conversion/0.1.0 --profile ./profile -f
conan test src/test_package/conanfile.py text_conversion/0.1.0@text_conversion/0.1.0 --profile ./profile
./build_wasm.sh
