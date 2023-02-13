
# About

Imagine you have a simple, nice, useful C++ function. How do you make it available to users?

# Content

The *full stack* contains:

* C++ header-only library with ```constexpr``` function.
* Compile-time unit-tests testing the above function.
* Command line tool to process command line arguments using the function.
* Command line tool to process interactive data using the function.
* A static library encapsulating this function.
* A unit test for this static library.
* A Python based Flask web-app providing a web-interface for the above command line tool.
* A docker container, containing the above Flask web-app.
* A Python module, implemented using the Python C API.

```mermaid
  flowchart TD;

    F(C++ Header File) --> CUT[Compile Time Unit Tests];

    F --> CLI1[Command Line Tool A]
    F --> CLI2[Command Line Tool B]
    F --> LIB(Static Lib)
    LIB --> LIBTEST[Static Lib Unit Test]

    F --> PY(Python Module)


    subgraph docker container
    CLI1 --> SERVER[Flask Web-App]
    end

    SERVER --> FRONT[Frontend]
    PY --> PYTEST[Python Unit Test]

```


# Requirements

* Local execution of the web-app requires Python 3.8+.
* Python module creation requires Python installation with Python C API dependencies.
* docker to containerize the web app.


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



