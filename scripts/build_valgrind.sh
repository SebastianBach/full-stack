cd ..

mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DADD_BASIC_TOOLS=ON -DBUILD_VALGRIND=ON .. 
cmake --build .
#valgrind --leak-check=full ctest
ctest -T memcheck 
cat ./Testing/Temporary/MemoryChecker.*.log
