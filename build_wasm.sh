trap 'echo "Error on build_wasm.sh"; exit 1' ERR

# copy data

if [ ! -d "./build/wasm/" ]; then
    mkdir ./build/wasm/
fi

BUILD_DIR=./build/wasm
SOURCE_DIR=./src/webassembly
PRODUCT_DIR=./build/product/webassembly/


# copy source files to $BUILD_DIR
cp $SOURCE_DIR/source.cpp $BUILD_DIR
cp ./src/header/text_conversion_constexpr.h $BUILD_DIR


# compile using container

FULL_PATH=$(pwd -W)/build/wasm/

docker run \
  --rm \
  -v $FULL_PATH:/src \
  -u $(id -u):$(id -g) \
  emscripten/emsdk \
  emcc source.cpp -s -std=c++20 -O2 -o title_case.js


# copy results to $PRODUCT_DIR

if [ ! -d "./build/product/webassembly" ]; then
    mkdir ./build/product/webassembly
fi

cp $BUILD_DIR/title_case.wasm $PRODUCT_DIR
cp $BUILD_DIR/title_case.js $PRODUCT_DIR
cp $SOURCE_DIR/index.html $PRODUCT_DIR
cp $SOURCE_DIR/styles.css $PRODUCT_DIR
cp $SOURCE_DIR/main.js $PRODUCT_DIR
