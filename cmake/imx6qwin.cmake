# this is required
SET(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# specify the cross compiler
SET(CMAKE_C_COMPILER E:/usr/linaro/gcc/bin/arm-linux-gnueabihf-gcc.exe)
SET(CMAKE_CXX_COMPILER E:/usr/linaro/gcc/bin/arm-linux-gnueabihf-g++.exe)

# where is the target environment 
SET(CMAKE_FIND_ROOT_PATH  E:/usr/linaro/gcc/)
SET(CMAKE_EXT_LIBRARAY_PATH  E:/usr/linaro/imx6q)
# search for programs in the build host directories (not necessary)
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)


SET(PASSOA_COMPILER_GCC TRUE)
add_definitions(-DPLAT_GCC)

set(Boost_INCLUDE_DIR e:/usr/linaro/imx6q/include/)
set(Boost_LIB_DIR e:/usr/linaro/imx6q/lib)

set(Boost_LIBs 
	boost_system-gcc-mt-1_65_1
	boost_filesystem-gcc-mt-1_65_1
	boost_thread_pthread-gcc-mt-1_65_1
	boost_locale-gcc-mt-1_65_1
	pthread
	dl
	)

