# About

You have a simple, nice, useful C++ function. How do you make it available to users?

# Content

The *full stack* contains:

* A C++ header-only library with a ``constexpr'' function.
* A compile-time unit test that tests the above function.
* A command-line tool to handle command-line arguments to the function.
* A Python UI application that provides a front-end to this command-line tool.
* A command line tool to handle interactive data with the function.
* A command-line tool to process the contents of a given file with the function.
* A static library that encapsulates the function.
* A unit test for this static library.
* A C++ QT5 UI application based on the static library.
* A *Conan 2* package containing the static library.
* A test for this *Conan* package.
* A dynamic library.
* A unit test for that dynamic library.
* A Python UI aplication using that dynamic library.
* A Python-based Flask web application that provides a web interface and REST API to the above command line tool.
* An HTML/JavaScript front end that queries the above REST API.
* A *Docker* container containing the above Flask web application.
* A Python module implemented using the Python C API.
* A unit test that tests this module.
* A Python UI application that uses this module.
* A WebAssembly binary library and associated JavaScript code.
* An HTML/JavaScript front end that uses the above WebAssembly library.
* A static library implementing a custom scripting language.
* A unit test for this static library.
* A console application for this scripting language.
* An interpreter that executes scripts in the custom scripting language.
* A compiler that converts scripts in the custom scripting language into bytecode.
* A runtime that executes that bytecode. 


```mermaid
  flowchart LR;

    F(C++ Function) --> CUT[Compile Time Unit Tests];

    F --> CLI1[Command Line Tool A]
    F --> CLI2[Command Line Tool B]
    F --> CLI3[Command Line Tool C]

    CLI1 --> PYAPP2[Python UI App]

    F --> LIB(Static Library)

    LIB --> LIBTEST[Static Lib Unit Test]
    LIB --> C(Conan Package)

    LIB --> QTCPP[C++ UI App]

    F --> DLL(Dynamic Library)
    DLL --> DLLTEST[Dynamic Lib Unit Test]
    DLL --> QTPYDLL[Python UI App]

    C --> CT[Conan Package Test]

    F --> PY(Python Module)

    subgraph docker container
    CLI1 --> SERVER[Flask Web-App]
    SERVER --> FRONT[Front End]
    end

    PY --> PYTEST[Python Unit Test]
    PY --> PYAPP[Python UI App]

    F --> WASM(WebAssembly + JavaScript)

    WASM --> WASMF[Front End]

    F --> SCRIPTLIB[Script Library]

    SCRIPTLIB --> SCRIPT_TEST[Script Unit Test]
    SCRIPTLIB --> SCRIPT_CONSOLE[Console]
    SCRIPTLIB --> SCRIPT_INTERPRETER[Interpreter]
    SCRIPTLIB --> SCRIPT_COMPILER[Compiler]
    SCRIPTLIB --> SCRIPT_RUNTIME[Runtime]
```


# Dependencies

* Native execution of the web app and other Python apps requires requires Python 3.8+.
* Python module creation requires Python installation with Python C API dependencies.
* *docker* to containerize the web app and to build the WebAssembly library.
* *conan* to build the *conan* package.
* *Qt5* to build the C++ Qt UI app.


# Build

To build and test everything:

```
# build all C++ products
mkdir build
cd build
cmake -DADD_PYTHON_MODULE=ON  -DADD_QT_APP=ON ..
cmake --build . --config Release
ctest -C Release  -VV
cmake --install .
cd ..

# run Python unit tests
python -m unittest discover src/test_py

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

- **ADD_PYTHON_MODULE**: To build the Python module (requires Python C API)
- **ADD_QT_APP**: To build a Qt5 UI app (requires Qt5).

# Usage

## Command Line Tool *title_case*

This command line tool takes the given command line argument, converts the data, and prints the result to ```std::cout```.

```
title_case "this is some text"

# prints
This is Some Text
```

## Command Line Tool *title_case_console*

Interactive command line tool. Enter the text to convert or "exit" to end the program.

## Command Line Tool *title_case_files*

The first command line argument is the file to read the data from, the second is the file to save the result to.

```
title_case_file source_file.txt target_file.txt
```

## Web App

Start the ```web.py``` script by providing the location of the resource files and the folder containing the ```title_case``` tool.

```
python web.py C:\web\resources C:\build\product
```

Open ```localhost:5000``` for a synchronous web app. Open ```localhost:5000/interactive``` for an asynchronous web app.

## Container

Build the *docker* image with:

```
docker build --tag title-case-web .
```

The multi-stage build process will build the ```title_case``` tool and copy all necessary files.


To start the container, run:

```
docker run --rm -it -p 5000:5000 title-case-web
```

Open ```localhost:5000``` for a synchronous web app. Open ```localhost:5000/interactive``` for an asynchronous web app.


## WebAssembly

WebAssembly requires to access the HTML document via a web server. A simple server can be started with Python:

```
python -m http.server
```

Open ```http://localhost:8000/``` to start the WebAssembly app.


## Scripting Language

The domain-specific scripting language is a simple language designed to perform basic tasks. The language consists of five commands:

| Command | Operand (optional) | Description |
| --- | --- | --- |
| **text** | *text to load and store in memory* | Stores the given text in the program's memory. |
| **process** | none | Processes the text in memory. |
| **print** | none | Prints the text in memory to the screen. |
| **load** | *path to text file* | Reads the specified text file and stores the text in memory. |
| **save** | *path to text file* | Saves the text in memory to the specified text file. |

An example program is:

```
text this is a headline
process
print
```

This will print ```This Is a Headline```.

## Command Line Tool *console*

The scripting **console** allows to enter and execute code. The console application can be closed by entering ```exit``` or pressing ```CTRL+C```.

## Command Line Tool *interpreter*

The **interpreter** loads and executes a script stored in the specified source file.

```
interpreter C:\scripts\script.txt
```

## Command Line Tool *compiler* & *runtime*

The **compiler** loads a source file and generates byte-code, that can be executed by the **runtime**.

```
compiler C:\scripts\script.txt C:\result\bytecode.code

runtime C:\result\bytecode.code
```
