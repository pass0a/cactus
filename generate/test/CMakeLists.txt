#cmake file for project association
#author: liuwenjun
#created:2014/02/20

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

## 添加项目

include_directories(${PROJECT_SOURCE_DIR}/src/)
include_directories(${PROJECT_SOURCE_DIR}/3rd/eigen)
include_directories(${PROJECT_SOURCE_DIR}/3rd/googletest/googletest/include)
include_directories(${PROJECT_SOURCE_DIR}/3rd/googletest/googletest/)
ADD_EXECUTABLE(cpptest
				${PROJECT_SOURCE_DIR}/test/index.cpp
				${PROJECT_SOURCE_DIR}/test/variables.cpp
				${PROJECT_SOURCE_DIR}/3rd/googletest/googletest/src/gtest-all.cc
				)
ADD_EXECUTABLE(mnist
				${PROJECT_SOURCE_DIR}/example/mnist/index.cpp)
ADD_EXECUTABLE(nn
				${PROJECT_SOURCE_DIR}/example/nn/index.cpp)
if(MSVC)
else()
target_link_libraries(cpptest pthread)
endif()
