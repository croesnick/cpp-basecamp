cmake_minimum_required (VERSION 2.8)

### Set common variables and parameters
##############################################################################

# set the project's name
set (PROJECT_NAME SampleProject)
project (${PROJECT_NAME} CXX)
# names for the shared library and the executable unit-tests
set (PROJECT_LIB_NAME SampleProjectLib)
set (PROJECT_TEST_NAME SampleProjectTest)

set (CMAKE_CXX_FLAGS
	"${CMAKE_CXX_FLAGS} -Wall -ggdb -Wno-deprecated -std=c++11 -pthread")

# project version number.
set(VERSION_MAJOR   0   CACHE STRING "Project major version number.")
set(VERSION_MINOR   0   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   1   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

### Library build options
##############################################################################

include_directories (${CMAKE_SOURCE_DIR}/include)
# add all cpp-files to the shared library
file (GLOB LIB_SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_library (${PROJECT_LIB_NAME} SHARED ${LIB_SRC_FILES})

### Configure googletest framework
##############################################################################

# enable ExternalProject CMake module necessary to include gtest
include (ExternalProject)

# Set default ExternalProject root directory.
# (gtest will be downloaded and installed there)
# Code found on
# http://stackoverflow.com/questions/9689183/cmake-googletest
set_directory_properties (PROPERTIES EP_PREFIX ${CMAKE_SOURCE_DIR}/ext)

# Add gtest
# Also see http://www.kitware.com/media/html/BuildingExternalProjectsWithCMake2.8.html 
ExternalProject_Add(
	# target name
	gtest
	# download step
	SVN_REPOSITORY http://googletest.googlecode.com/svn/trunk/
	SVN_REVISION -r 660
	TIMEOUT 10
	# Force separate output paths for debug and release builds to allow easy
	# identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
	CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
              -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
	           -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
	           -Dgtest_force_shared_crt=ON
	# Disables 'svn update'
	UPDATE_COMMAND ""
	# Disable install step
	INSTALL_COMMAND ""
	# Wrap download, configure and build steps in a script to log output
	LOG_DOWNLOAD ON
	LOG_CONFIGURE ON
	LOG_BUILD ON)

### Build the library and the tests
##############################################################################

# Specify the gtest include dir.
ExternalProject_Get_Property (gtest SOURCE_DIR)
include_directories (${CMAKE_SOURCE_DIR}/include)
include_directories (${SOURCE_DIR}/include)

file (GLOB TEST_SRC_FILES ${CMAKE_SOURCE_DIR}/test/*.cpp)
add_executable (${PROJECT_TEST_NAME} ${TEST_SRC_FILES})
add_dependencies (${PROJECT_TEST_NAME} gtest)

ExternalProject_Get_Property (gtest BINARY_DIR)
target_link_libraries (
	${PROJECT_TEST_NAME}
	# link with the shared library this project provides
	${PROJECT_LIB_NAME}
	# link with gtest
	${BINARY_DIR}/libgtest_main.a
	${BINARY_DIR}/libgtest.a)

add_test (NAME ${PROJECT_TEST_NAME} COMMAND ${PROJECT_TEST_NAME})
add_test (NAME SimpleQueueTest COMMAND ${PROJECT_TEST_NAME})
enable_testing ()

### Add Doxygen build target
##############################################################################

add_subdirectory (doc)
