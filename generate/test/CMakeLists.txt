#cmake file for project association
#author: liuwenjun
#created:2014/02/20

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

## 添加项目
find_package(FFTW REQUIRED)
include_directories(${FFTW_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/3rd/eigen)
ADD_EXECUTABLE(hpptest
				${PROJECT_SOURCE_DIR}/test/index.cpp
				#${PROJECT_SOURCE_DIR}/test/cactus.cpp
				${PROJECT_SOURCE_DIR}/test/catch.hpp
				)
ADD_EXECUTABLE(similarity
				${PROJECT_SOURCE_DIR}/example/similarity.cpp
				)
message("finding : " ${FFTW_FLOAT_LIB})
target_link_libraries(similarity ${FFTW_FLOAT_LIB})
target_link_libraries(hpptest ${FFTW_FLOAT_LIB})
