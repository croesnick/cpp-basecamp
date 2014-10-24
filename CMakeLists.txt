cmake_minimum_required (VERSION 2.8)

# set the project's name
set (PROJECT_NAME sample-project)
project (${PROJECT_NAME} CXX)

# gcc/clang won't enable C++11 features without this flag
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "(GNU|Clang)")
	set (CMAKE_CXX_FLAGS "-Wall -ggdb -Wno-deprecated -std=c++11")
endif()

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/include/)
# add all cpp-files to the shared library
file (GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_library (${PROJECT_NAME} SHARED ${SRC_FILES})
