cd ..
cd build
cmake  ..
cd ..
cd src
cd app_android

./gradlew assembleDebug

cp app/build/outputs/apk/debug/app-debug.apk ../../build/product/android/app-debug.apk
