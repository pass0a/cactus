#cmake file for project association
#author: liuwenjun
#created:2014/02/20

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

## 添加项目
include_directories(${PROJECT_SOURCE_DIR}/3rd/eigen)
ADD_EXECUTABLE(hpptest
				${PROJECT_SOURCE_DIR}/test/index.cpp
				#${PROJECT_SOURCE_DIR}/test/cactus.cpp
				${PROJECT_SOURCE_DIR}/test/catch.hpp
				)
find_package(FFTW REQUIRED)
find_package(PythonLibs)
include_directories(${FFTW_INCLUDE_DIRS})
ADD_EXECUTABLE(similarity
				${PROJECT_SOURCE_DIR}/example/similarity.cpp
				)
message("finding : " ${FFTW_FLOAT_LIB})
target_link_libraries(similarity ${FFTW_FLOAT_LIB})
target_include_directories(similarity PRIVATE ${PYTHON_INCLUDE_DIRS})
target_link_libraries(similarity ${PYTHON_LIBRARIES})
