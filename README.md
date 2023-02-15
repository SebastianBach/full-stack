
# About

Imagine you have a simple, nice, useful C++ function. How do you make it available to users?

# Content

The *full stack* contains:

* C++ header-only library with ```constexpr``` function.
* Compile-time unit tests testing the above function.
* Command line tool to process command line arguments using the function.
* Command line tool to handle interactive data with the function.
* A static library encapsulating the function.
* A unit test for this static library.
* A *conan* package containing this static library.
* A test for this *conan* package.
* A Python-based Flask web application that provides a web interface to the above command line tool.
* A Docker container containing the above Flask web application.
* A Python module implemented using the Python C API.
* A unit test that tests this Python module.

```mermaid
  flowchart TD;

    F(C++ Header File) --> CUT[Compile Time Unit Tests];

    F --> CLI1[Command Line Tool A]
    F --> CLI2[Command Line Tool B]

    F --> LIB(Static Lib)

    LIB --> LIBTEST[Static Lib Unit Test]
    LIB --> C(Conan Package)

    C --> CT[Conan Package Test]

    F --> PY(Python Module)

    subgraph docker container
    CLI1 --> SERVER[Flask Web-App]
    SERVER --> FRONT[Frontend]
    end

    PY --> PYTEST[Python Unit Test]
```


# Requirements

* Local execution of the web-app requires Python 3.8+.
* Python module creation requires Python installation with Python C API dependencies.
* *docker* to containerize the web app.
* *conan* to build the *conan* package.


# Build

To build and test everything:

```
mkdir build
cd build
cmake -DADD_PYTHON_MODULE=ON .. 
cmake --build . --config Release --target compile_tests
cmake --build . --config Release --target cmdl
cmake --build . --config Release --target cmdl_interactive
cmake --build . --config Release --target func_lib
cmake --build . --config Release --target lib_test
cmake --build . --config Release --target python_module
ctest -C Release  -VV
cmake --install .
cd ..
python -m unittest discover src/test_py
docker build --tag func_app .
conan export-pkg . func_lib/0.1.0 --profile ./profile -f
conan test src/test_package/conanfile.py func_lib/0.1.0@func_lib/0.1.0 --profile ./profile
```

The collection of deliverables can be found in ```build/product```.

# Use


## Web-App

```
python web.py C:\web\resources C:\build\product
```

## Container

Build the image with:
```
docker build --tag func_app .
```
The multi-stage build process will build the ```cmdl``` tool.


Run the container with:
```
docker run -it -p 5000:5000 func_app
```

# ToDo



