#cmake file for project association
#author: liuwenjun
#created:2014/02/20

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

include_directories(${PROJECT_SOURCE_DIR}/3rd/eigen)
add_definitions(-DCxAPI_EXPORTS)
add_library(cactus SHARED
				${PROJECT_SOURCE_DIR}/src/core/framework/tensor.cpp
				${PROJECT_SOURCE_DIR}/src/core/framework/buffer.cpp
				${PROJECT_SOURCE_DIR}/src/core/framework/node.cpp
				${PROJECT_SOURCE_DIR}/src/core/framework/graph.cpp
				${PROJECT_SOURCE_DIR}/src/core/kernels/backward.cpp
				${PROJECT_SOURCE_DIR}/src/core/kernels/ops.cpp
				${PROJECT_SOURCE_DIR}/src/core/operator/add.cpp
				${PROJECT_SOURCE_DIR}/src/core/operator/sub.cpp
				${PROJECT_SOURCE_DIR}/src/core/operator/product.cpp
				${PROJECT_SOURCE_DIR}/src/core/operator/div.cpp
				${PROJECT_SOURCE_DIR}/src/core/operator/dot.cpp
				${PROJECT_SOURCE_DIR}/src/core/operator/pow.cpp
				${PROJECT_SOURCE_DIR}/src/core/operator/sum.cpp
				${PROJECT_SOURCE_DIR}/src/core/operator/matmul.cpp
				${PROJECT_SOURCE_DIR}/src/core/operator/assign.cpp
				${PROJECT_SOURCE_DIR}/src/core/operator/flow.cpp
				${PROJECT_SOURCE_DIR}/src/core/operator/logic.cpp
				)
