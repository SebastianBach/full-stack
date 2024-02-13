

cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DADD_PYTHON_MODULE=ON  -DADD_QT_APP=ON -DADD_RUST_APP=ON ..
cppcheck --project=compile_commands.json --cppcheck-build-dir=./temp/cppcheck
cmake --build . --target clean
cmake --build . -j --config Release
ctest -C Release  -VV
cmake --install .

cd lib_example_build
cmake  ../product/lib/example
cmake --build . --config Release
ctest -C Release  -VV
cd ..
cd ..

# static lib documentation
doxygen build/doxyfile 

# run Python unit tests
python3 -m unittest discover src/test_py