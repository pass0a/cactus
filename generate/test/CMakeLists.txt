#cmake file for project association
#author: liuwenjun
#created:2014/02/20

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

## 添加项目
find_package(FFTW REQUIRED)
include_directories(${FFTW_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/3rd/eigen)
include_directories(${PROJECT_SOURCE_DIR}/3rd/fmt/include)

ADD_EXECUTABLE(hpptest
				${PROJECT_SOURCE_DIR}/test/index.cpp
				#${PROJECT_SOURCE_DIR}/test/cactus.cpp
				${PROJECT_SOURCE_DIR}/test/catch.hpp
				)
ADD_EXECUTABLE(lcstest
				${PROJECT_SOURCE_DIR}/test/idea.cpp
				#${PROJECT_SOURCE_DIR}/test/cactus.cpp
				${PROJECT_SOURCE_DIR}/test/catch.hpp
				)
ADD_EXECUTABLE(audio_build
				${PROJECT_SOURCE_DIR}/example/audio_build.cpp
				${PROJECT_SOURCE_DIR}/example/audio_feature.cpp
				${PROJECT_SOURCE_DIR}/example/simhash.cpp
				${PROJECT_SOURCE_DIR}/example/sqlite/sqlite3.c
				)
ADD_EXECUTABLE(audio_search
				${PROJECT_SOURCE_DIR}/example/audio_search.cpp
				${PROJECT_SOURCE_DIR}/example/audio_feature.cpp
				${PROJECT_SOURCE_DIR}/example/sqlite/sqlite3.c
				)
message("finding : " ${FFTW_FLOAT_LIB})
target_link_libraries(audio_build ${FFTW_FLOAT_LIB} pthread dl)
target_link_libraries(audio_search ${FFTW_FLOAT_LIB} pthread dl)
target_link_libraries(hpptest ${FFTW_FLOAT_LIB})
