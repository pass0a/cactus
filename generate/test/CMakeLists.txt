#cmake file for project association
#author: liuwenjun
#created:2014/02/20

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

## 添加项目
include_directories(D:/dev/python36/Lib/site-packages/numpy/core/include)
include_directories(D:/dev/python36/include)
link_directories(D:/dev/python36/libs)
include_directories(${PROJECT_SOURCE_DIR}/3rd/eigen)
include_directories(${PROJECT_SOURCE_DIR}/3rd/googletest/googletest/include)
include_directories(${PROJECT_SOURCE_DIR}/3rd/googletest/googletest/)
include_directories(E:/git/tiny-dnn)
ADD_EXECUTABLE(cpptest
				${PROJECT_SOURCE_DIR}/test/index.cpp
				${PROJECT_SOURCE_DIR}/test/variables.cpp
				${PROJECT_SOURCE_DIR}/3rd/googletest/googletest/src/gtest-all.cc
				)
ADD_EXECUTABLE(hpptest
				${PROJECT_SOURCE_DIR}/test/index.cpp
				${PROJECT_SOURCE_DIR}/test/cactus.cpp
				${PROJECT_SOURCE_DIR}/3rd/googletest/googletest/src/gtest-all.cc
				)
ADD_EXECUTABLE(mnist
				${PROJECT_SOURCE_DIR}/example/mnist/index.cpp)
ADD_EXECUTABLE(perceptron
				${PROJECT_SOURCE_DIR}/example/line/perceptron.cpp)
ADD_EXECUTABLE(linear-regression
				${PROJECT_SOURCE_DIR}/example/line/linear-regression.cpp)
ADD_EXECUTABLE(tinydnntest
				${PROJECT_SOURCE_DIR}/test/index.cpp
				${PROJECT_SOURCE_DIR}/test/tinydnntest.cpp
				${PROJECT_SOURCE_DIR}/3rd/googletest/googletest/src/gtest-all.cc
				)