
# Basic Command Line Tools

## Command Line Tool ```title_case```

This command line tool takes the given command line argument, converts the data, and prints the result to ```std::cout```.

```
title_case "this is some text"

# prints
This is Some Text
```

## Command Line Tool ```title_case_console```

Interactive command line tool. Enter the text to convert or "exit" to end the program.

## Command Line Tool ```title_case_files```

The first command line argument is the file to read the data from, the second is the file to save the result to.

```sh
title_case_file source_file.txt target_file.txt
```

# Web Applications

## Local Usage

Start the ```web.py``` script by providing the location of the resource files and the folder containing the ```title_case``` tool.

```sh
python web.py C:\web\resources C:\build\product
```

Open ```localhost:5000``` for a synchronous web app. Open ```localhost:5000/interactive``` for an asynchronous web app.

## Container

Build the *docker* image with:

```sh
docker build --tag title-case-web .
```

The multi-stage build process will build the ```title_case``` tool and copy all necessary files.


To start the container, run:

```sh
docker run --rm -it -p 5000:5000 title-case-web
```

Open ```localhost:5000``` for a synchronous web app. Open ```localhost:5000/interactive``` for an asynchronous web app.


## WebAssembly Web App

WebAssembly requires to access the HTML document via a web server. A simple server can be started with Python:

```sh
python -m http.server
```

Open ```http://localhost:8000/``` to start the WebAssembly app.


# Scripting Language

The domain-specific scripting language is a simple language designed to perform basic tasks. The language consists of five commands:

| Command | Operand (optional) | Description |
| --- | --- | --- |
| ```text``` | *text to load and store in memory* | Stores the given text in the program's memory. |
| ```process``` | - | Processes the text in memory. |
| ```print``` | - | Prints the text in memory to the screen. |
| ```load``` | *path to text file* | Reads the specified text file and stores the text in memory. |
| ```save``` | *path to text file* | Saves the text in memory to the specified text file. |

An example program is:

```
text this is a headline
process
print
```

This will print ```This Is a Headline```.

## Command Line Tool ```console```

The scripting **console** allows to enter and execute code. The console application can be closed by entering ```exit``` or pressing ```CTRL+C```.

## Command Line Tool ```interpreter```

The **interpreter** loads and executes a script stored in the specified source file.

```sh
interpreter script.txt
```

## Command Line Tool ```compiler``` & ```runtime```

The **compiler** loads a source file and generates byte-code, that can be executed by the **runtime**.

```sh
compiler script.txt bytecode.code

runtime bytecode.code
```

## Command Line Tool ```transcompiler```

The **transcompiler** loads a source file and generates equivalent code in another programming language.
It also performs code optimisations.


```sh
transcompiler script.txt python_script.py py
```

The arguments are:

* Path to the script source file.
* Path to the target file to create.
* The target language. 

Supported targets are:

* ```py```: Python using the ```text_conversion``` module.
* ```cpp```: C++ using the C++ library.
* ```linux_x86_64```:Linux x86 64 assembly using the C library.
* ```i```: The intermediate representation.

# Java Command Line Tool

Execute the command line tool (JAR) like this:

```sh
java -jar text_conversion.jar "this is a headline"
```

Make sure the ```libjava_text_conversion``` shared library can be found by Java. Set the command line argument ```java.library.path``` if needed.

# Jupyter Notebook

Start the Jupyter Notebook by simply running the ```start_notebook.sh``` script. It will start the notebook server with the notebook selected.

# Assembly Command Line Tool

The command line tool written in assembly is used like this:

```shell
title_case "this is a headline"

# will print
# Input:  this is a headline
# Output: This Is a Headline
```
