# mkdir fmt
# cd fmt
# cmake ../../3rd/fmt -DCMAKE_INSTALL_PREFIX=../../stage
# cmake --build ./ --target install --config Release
# cd ..
mkdir linux
cd linux
cmake ../../generate -DCACTUS_TEST=ON -DCACTUS_MAIN=ON -DCMAKE_INSTALL_PREFIX=../../stage -DCMAKE_EXPORT_COMPILE_COMMANDS=YES
cmake --build ./ --config Release
