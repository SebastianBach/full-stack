Build instructions


# Dependencies

* Native execution of the web app and other Python apps requires requires Python 3.8+.
* Python module creation requires Python installation with Python C API dependencies.
* *docker* to containerize the web app and to build the WebAssembly library.
* *conan* to build the *conan* package.
* *Qt5* to build the C++ Qt UI app.
* *Rust* to build the Rust app.
* *Java* to build Java command line tool.


# Build Overview

To build and test everything:

```
# build all C++ products
mkdir build
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

# test lib example project
cd lib_example_build
cmake  ../product/lib/example
cmake --build . --config Release
ctest -C Release  -VV
cd ..
cd ..

# build web app container
docker build --tag title-case-web .

# build and test conan package
conan export-pkg . 
conan list text_conversion
conan test ./src/test_package text_conversion/0.1.1

# build WebAssembly library
./build_wasm.sh
```

The collection of deliverables can be found in ```build/product```.

CMake options are:

- **ADD_BASIC_TOOLS**: To build the basic command line tools.
- **ADD_SDK**: To build the static library and documentation.
- **ADD_C_LIB**: To build a static library with C interface.
- **ADD_DYNAMIC_LIB**: To build a dynamic library.
- **ADD_PYTHON_MODULE**: To build the Python module (requires Python C API).
- **ADD_PY_DOCS**: To build the Python documentation (requires Sphinx).
- **ADD_LIB_DOCS**: To build the C++ library documentation (requires doxygen).
- **ADD_QT_APP**: To build a Qt5 UI app (requires Qt5).
- **ADD_RUST_APP**: To build the Rust command line tool (requires Rust).
- **ADD_JAVA_APP**: To build the Java command line tool (requires Java).
- **ADD_SCRIPT_TOOLS**: To build the script tools.
- **ADD_ASSEMBLY_PROGRAM**: To build the Assembly program.
- **ADD_WIN_TOOLS**: To build Windows utilities.

See also ```.github/workflows/build.yml```.

# Building the Basic Command Line Tools


# Building the Scripting Tools


# Building the SDK


# Building the QT UI Application


# Building the Rust Command Line Tool


# Building the Assembly Command Line Tool


# Building the WebAssembly Web Application

