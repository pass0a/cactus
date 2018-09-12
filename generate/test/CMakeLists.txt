#cmake file for project association
#author: liuwenjun
#created:2014/02/20

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

## 添加项目
if(PASSOA_COMPILER_MSVC)
include_directories(${PROJECT_SOURCE_DIR}/3rd/eigen)
ADD_EXECUTABLE(cpptest
				${PROJECT_SOURCE_DIR}/test/index.cpp
				${PROJECT_SOURCE_DIR}/test/variables.cpp
				${PROJECT_SOURCE_DIR}/test/perceptron.cpp
				${PROJECT_SOURCE_DIR}/src/tensor.cpp
				${PROJECT_SOURCE_DIR}/src/matrix.cpp
				)
target_link_libraries(cpptest
				debug gtestd
				optimized gtest)
endif()
