#cmake file for project association
#author: liuwenjun
#created:2014/02/20

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

## 添加项目
include_directories(${PROJECT_SOURCE_DIR}/3rd/eigen)
ADD_EXECUTABLE(hpptest
				${PROJECT_SOURCE_DIR}/test/index.cpp
				${PROJECT_SOURCE_DIR}/test/cactus.cpp
				${PROJECT_SOURCE_DIR}/test/catch.hpp
				)
