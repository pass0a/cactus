mkdir linux
cd linux
cmake ../../generate -DCACTUS_TEST=ON -DCACTUS_MAIN=ON -DCMAKE_INSTALL_PREFIX=./pack -DCMAKE_EXPORT_COMPILE_COMMANDS=YES
cmake --build ./
