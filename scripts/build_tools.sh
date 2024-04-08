cd ..
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DADD_BASIC_TOOLS=ON .. 
cmake --build . --config Release
cmake --install .
