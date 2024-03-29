echo test transcompiler

cd ..

cd build
cmake -DCMAKE_BUILD_TYPE=Release -DADD_SCRIPT_TOOLS=ON -DADD_PYTHON_MODULE=ON ..

cmake --build . -j --config Release
ctest -C Release
cmake --install .

cd temp
mkdir test_transcompiler
cd test_transcompiler


mkdir cpp
cd cpp

./../../../src/script_transcompiler/transcompiler "../../../../src/script_resources/script_test.txt" "result.cpp" "cpp"

g++ result.cpp -o transcompiler_result -ltext_conversion -L../../../product/lib/lib -I../../../product/lib/header

echo run binary:

./transcompiler_result


cd ..
mkdir intermediate
cd intermediate

./../../../src/script_transcompiler/transcompiler "../../../../src/script_resources/script_test.txt" "result.txt" "i"


cd ..
mkdir py
cd py

./../../../src/script_transcompiler/transcompiler "../../../../src/script_resources/script_test.txt" "result.py" "py"

echo run python script:

export PYTHONPATH=$PYTHONPATH:../../../product/python
python3 result.py

cd ..
mkdir linux_x86_64
cd linux_x86_64

echo build linux_x86_64

./../../../src/script_transcompiler/transcompiler "../../../../src/script_resources/script_test.txt" "result.s" "linux_x86_64"

gcc  -o result result.s ../../../product/rust/libtext_conversion_c.a -m64 -lc -nostartfiles

echo run binary from assembly:

./result
