
set GENERATOR=Ninja

if exist ninja rd ninja /S/Q
mkdir ninja
cd ninja

cmake ../../generate -G "%GENERATOR%" -DCMAKE_INSTALL_PREFIX=./pack -DCMAKE_CXX_COMPILER=clang-cl
rem cmake --build ./ --target install
cd ..
pause