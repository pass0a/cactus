
SET(PASSOA_COMPILER_GCC TRUE)
add_definitions(-DPLAT_GCC)
set(BOOST_ROOT /usr/local/)
find_package(Boost REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(Boost_FOUND)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} )
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS} )
endif()

set(Boost_LIBs 
    boost_system
    boost_filesystem
    boost_thread
    boost_chrono
    pthread
    dl
    )

