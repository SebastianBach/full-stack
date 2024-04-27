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

```shell
# build all C++ products
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release    -DADD_BASIC_TOOLS=ON\
                                    -DADD_SDK=ON\
                                    -DADD_SDK_DOCS=ON\
                                    -DADD_C_LIB=ON\
                                    -DADD_DYNAMIC_LIB=ON\
                                    -DADD_PYTHON_MODULE=ON\
                                    -DADD_QT_APP=ON\
                                    -DADD_RUST_APP=ON\
                                    -DADD_PY_DOCS=ON\
                                    -DADD_SCRIPT_TOOLS=ON\
                                    -DADD_ASSEMBLY_PROGRAM=ON ..
cmake --build . -j
ctest
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

# Building Specific Tools

## Building the Basic Command Line Tools

Building the basic command line tools requires:

- **cmake**
- C++20 compatible compiler

```shell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DADD_BASIC_TOOLS=ON .. 
cmake --build . 
ctest
cmake --install .
```


## Building the Scripting Tools

Building the scripting tools requires:

- **cmake**
- C++20 compatible compiler

```shell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -ADD_SCRIPT_TOOLS=ON .. 
cmake --build . 
ctest
cmake --install .
```


## Building the SDK

Building the scripting tools requires:

- **cmake**
- C++20 compatible compiler
- **doxygen** for the HTML documentation

```shell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release  -DADD_SDK=ON\
                                  -DADD_SDK_DOCS=ON .. 
cmake --build . 
ctest
cmake --install .
```


## Building the QT UI Application

Building the QT UI application requires:

- **cmake**
- C++20 compatible compiler to build the SDK
- **QT5**

```shell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release  -DADD_SDK=ON\
                                  -DADD_QT_APP=ON .. 
cmake --build . 
ctest
cmake --install .
```


## Building the Rust Command Line Tool

Building the Rust command line tool requires:

- **cmake**
- C++20 compatible compiler
- **Cargo** Rust compiler

```shell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release  -DADD_C_LIB=ON\
                                  -DADD_RUST_APP=ON .. 
cmake --build . 
ctest
cmake --install .
```


## Building the Assembly Command Line Tool

Building the assembly command line tool requires:

- **cmake**
- C++20 compatible compiler

```shell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release  -DADD_C_LIB=ON\
                                  -DADD_ASSEMBLY_PROGRAM=ON .. 
cmake --build . 
ctest
cmake --install .
```


## Building the WebAssembly Web Application

To build the WebAssembly application, it is recommended to use **docker** to run **emscripten/emsdk**.

See **build_wasm.sh**

## Building the Docker Container

Building the docker container with the web application requires:

* **docker**

```shell
docker build --tag title-case-web .
```

## Building the Android App

Building the Android App requires:

* Java Development Kit
* Android SDK
* Android NDK
* Gradle

```shell
# dev build

mkdir build
cd build
cmake  ..

cd ..
cd src
cd app_android

./gradlew assembleDebug

cp app/build/outputs/apk/debug/app-debug.apk ../../build/product/android/app-debug.apk
```
