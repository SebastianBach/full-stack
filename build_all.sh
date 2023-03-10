trap 'echo "Error: Command failed"; exit 1' ERR

if [ ! -d "build" ]; then
    echo "make build folder"
    mkdir build
fi

cd build
cmake -DADD_PYTHON_MODULE=ON -DADD_QT_APP=ON ..
cmake --build . --config Release
ctest -C Release  -VV
cmake --install .
cd ..
python -m unittest discover src/test_py
docker build --tag title-case-web .
conan export-pkg . text_conversion/0.1.0 --profile ./profile -f
conan test src/test_package/conanfile.py text_conversion/0.1.0@text_conversion/0.1.0 --profile ./profile
./build_wasm.sh
