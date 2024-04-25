rm -r ./build
mkdir build

g++ src/main.cpp -o build/main

./build/main >> ./build/output.ppm

ffmpeg -i ./build/output.ppm ./build/output.png
code "./build/output.png"