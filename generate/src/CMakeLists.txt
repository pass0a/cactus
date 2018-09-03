#cmake file for project association
#author: liuwenjun
#created:2014/02/20

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

if(PASSOA_COMPILER_MSVC)
include_directories(${PROJECT_SOURCE_DIR}/3rd/eigen)
ADD_EXECUTABLE(cactus
				${PROJECT_SOURCE_DIR}/src/index.cpp
				)
endif()
