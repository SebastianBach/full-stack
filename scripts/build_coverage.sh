cd ..

rm -rf build/
mkdir build
cd build
cmake -DBUILD_COVERAGE=ON -DADD_PYTHON_MODULE=ON  -DADD_QT_APP=ON -DADD_RUST_APP=ON ..
cmake --build . -j 
ctest -VV
cmake --install .
cd ..

# static lib documentation
doxygen build/doxyfile 

# run Python unit tests
python3 -m unittest discover src/test_py

gcovr -r . --html --html-details -o build/temp/coverage/coverage.html