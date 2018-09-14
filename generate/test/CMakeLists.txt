#cmake file for project association
#author: liuwenjun
#created:2014/02/20

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

## 添加项目
include_directories(${PROJECT_SOURCE_DIR}/src/core)
include_directories(${PROJECT_SOURCE_DIR}/3rd/eigen)
include_directories(${PROJECT_SOURCE_DIR}/3rd/googletest/googletest/include)
include_directories(${PROJECT_SOURCE_DIR}/3rd/googletest/googletest/)
ADD_EXECUTABLE(cpptest
				${PROJECT_SOURCE_DIR}/test/index.cpp
				${PROJECT_SOURCE_DIR}/test/variables.cpp
				${PROJECT_SOURCE_DIR}/test/perceptron.cpp
				${PROJECT_SOURCE_DIR}/src/core/framework/tensor.cpp
				${PROJECT_SOURCE_DIR}/src/core/kernels/math.cpp
				${PROJECT_SOURCE_DIR}/3rd/googletest/googletest/src/gtest-all.cc
				)
#target_link_libraries(cpptest
				#debug gtestd
				#optimized gtest
				#gtest)
