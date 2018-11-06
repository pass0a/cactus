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
ADD_EXECUTABLE(perceptron
				${PROJECT_SOURCE_DIR}/example/line/perceptron.cpp)
ADD_EXECUTABLE(linear-regression
				${PROJECT_SOURCE_DIR}/example/line/linear-regression.cpp)

if(MSVC)
target_link_libraries(cpptest cactus)
target_link_libraries(mnist cactus)
target_link_libraries(linear-regression cactus)
target_link_libraries(perceptron cactus)
else()
target_link_libraries(cpptest pthread cactus)
target_link_libraries(mnist pthread cactus)
target_link_libraries(nn pthread cactus)
endif()
