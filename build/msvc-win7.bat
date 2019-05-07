set TOOLCHAIN="-DCMAKE_TOOLCHAIN_FILE=../../cmake/msvc.cmake"
set GENERATOR=Visual Studio 14 2015

if exist x32win rd x32win /S/Q
mkdir x32win
cd x32win

cmake ../../generate -G "%GENERATOR%" %TOOLCHAIN% -DCMAKE_INSTALL_PREFIX=./pack -DFFTW_ROOT=E:\downloads\fftw-3.3.5-dll32 
cmake --build ./
cd ..
pause