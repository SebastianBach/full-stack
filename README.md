[![builds](https://github.com/SebastianBach/full-stack/actions/workflows/build.yml/badge.svg)](https://github.com/SebastianBach/full-stack/actions/workflows/build.yml)

Coverage: https://sebastianbach.github.io/full-stack/coverage.html

# About

You have a simple, nice, useful C++ function. How do you make it available to consumers?

# Content

The *full stack* contains:

* A C++ header-only library with a ```constexpr``` function.
* A compile-time unit test that tests the above function.
* A command line utility to handle command line arguments to the function.
* A Python UI application that provides a front-end to this command-line tool.
* A command line tool to handle interactive data with the function.
* A command line tool to process the contents of a given file with the function.
* A static library encapsulating the function.
* A unit test for this static library.
* A sample project for this static library.
* A C++ QT5 UI application based on the static library.
* A *Conan 2* package containing the static library.
* A test for this *Conan* package.
* A dynamic library.
* A unit test for this dynamic library.
* A Python UI application that uses this dynamic library.
* A Python-based Flask web application that provides a web interface and REST API to the above command line tool.
* An HTML/JavaScript front-end that queries the above REST API.
* A *Docker* container containing the above Flask web application.
* A Python module implemented using the Python C API.
* A unit test that tests this module.
* A *Sphinx* documentation for this module.
* A *Jupyter notebook* showing how to use this module.
* A *marimo* notebook using this module.
* A Python UI application that uses this module.
* A WebAssembly binary library and associated JavaScript code.
* An HTML/JavaScript frontend that uses the above WebAssembly library.
* A static library that implements a custom scripting language.
* A unit test for this static library.
* A console application for that scripting language.
* An interpreter that executes scripts in the custom scripting language.
* A Python-based IDE front-end for this script interpreter.
* A compiler that converts scripts in the custom scripting language into bytecode.
* A runtime that executes this bytecode.
* A transcompiler that creates Python or C++ code based on a given script written in the custom scripting language.
* A C-wrapper library for the C++ function.
* A unit test that tests this C-wrapper library.
* A program written in Assembly language that utilizes this C-wrapper library.
* A *Rust* command line tool calling the C-wrapper library function.
* A Java Native Interface Library to extend Java.
* A unit test for that library.
* A *Java* command line tool using that library.
* A *Windows* utility library.
* A unit test for this utility library.
* A *Windows* system tray app using the utility library.
* An *Android* app.

```mermaid
  flowchart LR;

    F(C++ Function) --> CUT[Compile Time Unit Tests];

    F --> CLI1[Command Line Tool A]
    F --> CLI2[Command Line Tool B]
    F --> CLI3[Command Line Tool C]

    CLI1 --> PYAPP2[Python UI App]

    F --> LIB(Static Library)
    
    subgraph SDK
    LIB --> DOXYGEN(Doxygen Documentation)
    LIB --> LIBEX[Static Lib Example Project]
    end

    LIB --> LIBTEST[Static Library Unit Test]
    LIB --> C(Conan Package)

    LIB --> QTCPP[C++ UI App]

    F --> DLL(Dynamic Library)
    DLL --> DLLTEST[Dynamic Library Unit Test]
    DLL --> QTPYDLL[Python UI App]

    C --> CT[Conan Package Test]

    F --> PY(Python Module)

    subgraph docker container
    CLI1 --> SERVER[Flask Web-App]
    SERVER --> FRONT[Front End]
    end

    PY --> PYTEST[Python Module Unit Test]
    PY --> SPHINX(Sphinx Documentation)
    PY --> NOTEBOOK[Jupyter Notebook] 
    PY --> MARIMO[Marimo Notebook]  
    PY --> PYAPP[Python UI App]

    F --> WASM(WebAssembly + JavaScript)

    WASM --> WASMF[Front End]

    F --> SCRIPTLIB(Script Library)

    SCRIPTLIB --> SCRIPT_TEST[Script Library Unit Test]
    SCRIPTLIB --> SCRIPT_CONSOLE[Console]
    SCRIPTLIB --> SCRIPT_INTERPRETER[Interpreter]
    SCRIPT_INTERPRETER --> SCRIPT_IDE[IDE]
    SCRIPTLIB --> SCRIPT_COMPILER[Compiler]
    SCRIPTLIB --> SCRIPT_RUNTIME[Runtime]
    SCRIPTLIB --> SCRIPT_CONVERT[Transcompiler]

    F --> CWRAPPER(C Wrapper Lib)
    CWRAPPER --> CWRAPPER_TEST[C Wrapper Unit Test]
    CWRAPPER --> RUST_APP[Rust Command Line Tool]  
    CWRAPPER --> ASM[Assembly Program] 

    F --> JAVA_LIB(Java Native Interface Library)
    JAVA_LIB --> JAVA_UNIT_TEST[Java Unit Test]  
    JAVA_LIB --> JAVA_APP[Java CLI Tool] 

    F --> WIN_LIB(Windows Utility Library)
    WIN_LIB --> WIN_LIB_TEST[Library Unit Test]
    WIN_LIB --> WIN_TRAY[Windows System Tray Tool]

    F --> ANDROID[Android App] 
```

# Build

See the [build instructions](doc/build.md) on how to build the included software.

# Usage

See the [user guide](doc/user_guide.md) on how to use the included software.
