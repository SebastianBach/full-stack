if not exist ".\build\wasm\" mkdir .\build\wasm

set BUILD_DIR=.\build\wasm
set SOURCE_DIR=.\src\webassembly
set PRODUCT_DIR=.\build\product\webassembly

REM copy source files to %BUILD_DIR%
copy %SOURCE_DIR%\source.cpp %BUILD_DIR%
copy .\src\header\text_conversion_constexpr.h %BUILD_DIR%

REM compile using container

for /f "delims=" %%i in ('cd') do set FULL_PATH=%%i\build\wasm\

docker run --rm -v %FULL_PATH%:/src  emscripten/emsdk emcc source.cpp -s -std=c++20 -O2 -o title_case.js



if not exist ".\build\product\webassembly" mkdir .\build\product\webassembly

copy %BUILD_DIR%\title_case.wasm %PRODUCT_DIR%
copy %BUILD_DIR%\title_case.js %PRODUCT_DIR%
copy %SOURCE_DIR%\index.html %PRODUCT_DIR%
copy %SOURCE_DIR%\styles.css %PRODUCT_DIR%
copy %SOURCE_DIR%\main.js %PRODUCT_DIR%

