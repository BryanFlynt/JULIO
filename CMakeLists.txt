# Check CMake Version 
cmake_minimum_required(VERSION 3.8.0 FATAL_ERROR)

#
#---------------------------------------------------------------------
# Project Setup
#---------------------------------------------------------------------
#
project("JSON" VERSION 1.0.0.0 LANGUAGES CXX)

#---------------------------------------------------------------------
# User Configure Build Process
#---------------------------------------------------------------------
set(CMAKE_VERBOSE_MAKEFILE OFF)
if(NOT CMAKE_BUILD_TYPE)
	set(
		CMAKE_BUILD_TYPE Release 
		CACHE STRING 
		"Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel"
		)
endif()
if(NOT BUILD_TESTING)
	set(
		BUILD_TESTING ON
		CACHE STRING 
		"Turn ON/OFF compilation of testing code"
		)
endif()
if(NOT CMAKE_VERBOSE_MAKEFILE)
	set(
		CMAKE_VERBOSE_MAKEFILE OFF
		CACHE STRING 
		"Turn ON/OFF Verbose messages from Makefile"
		)
endif()


# Control message level of CMake
# Should be set on command line as follow by user
# --log-level=<ERROR|WARNING|NOTICE|STATUS|VERBOSE|DEBUG|TRACE>
# --loglevel=  Older versions of CMake
set(CMAKE_MESSAGE_LOG_LEVEL STATUS)

#---------------------------------------------------------------------
# Set location of *.cmake modules
#---------------------------------------------------------------------
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

#---------------------------------------------------------------------
# Force build in seperate directory
#---------------------------------------------------------------------
include(InSourceBuild)

#---------------------------------------------------------------------
# Directory Report
#---------------------------------------------------------------------
message(VERBOSE "")
message(VERBOSE "")
message(VERBOSE "--------------------- Directory Report -----------------------")
message(VERBOSE "") # CMAKE directories are from top level CMakeLists.txt
message(VERBOSE "Top Level Directories:")
message(VERBOSE "CMAKE_SOURCE_DIR  = ${CMAKE_SOURCE_DIR}")
message(VERBOSE "CMAKE_BINARY_DIR  = ${CMAKE_BINARY_DIR}")
message(VERBOSE "") # PROJECT directories are for recent project call
message(VERBOSE "Project Level Directories:")
message(VERBOSE "PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message(VERBOSE "PROJECT_BINARY_DIR = ${PROJECT_BINARY_DIR}")


#---------------------------------------------------------------------
# Locations of Installation & Report
#---------------------------------------------------------------------

# Source locations in source tree
set(MY_PROJECT_PREFIX ${PROJECT_SOURCE_DIR})
set(MY_PROJECT_INCDIR ${MY_PROJECT_PREFIX}/include)
set(MY_PROJECT_SRCDIR ${MY_PROJECT_PREFIX}/src)
set(MY_PROJECT_TSTDIR ${MY_PROJECT_PREFIX}/test)

# Where to place all libraries
set(MY_INSTALL_PREFIX ${CMAKE_BINARY_DIR})
set(MY_INSTALL_INCDIR ${MY_INSTALL_PREFIX}/include)
set(MY_INSTALL_SRCDIR ${MY_INSTALL_PREFIX}/src)
set(MY_INSTALL_LIBDIR ${MY_INSTALL_PREFIX}/lib)
set(MY_INSTALL_TSTDIR ${MY_INSTALL_PREFIX}/test)

message(VERBOSE " ")
message(VERBOSE "Using Directories:")
message(VERBOSE "--- Original Locations ---")
message(VERBOSE "MY_PROJECT_PREFIX = ${MY_PROJECT_PREFIX}")
message(VERBOSE "MY_PROJECT_INCDIR = ${MY_PROJECT_INCDIR}")
message(VERBOSE "MY_PROJECT_SRCDIR = ${MY_PROJECT_SRCDIR}")
message(VERBOSE "MY_PROJECT_TSTDIR = ${MY_PROJECT_TSTDIR}")
message(VERBOSE " ")
message(VERBOSE "--- Installation Locations ---")
message(VERBOSE "MY_INSTALL_PREFIX = ${MY_INSTALL_PREFIX}")
message(VERBOSE "MY_INSTALL_INCDIR = ${MY_INSTALL_INCDIR}")
message(VERBOSE "MY_INSTALL_SRCDIR = ${MY_INSTALL_SRCDIR}")
message(VERBOSE "MY_INSTALL_LIBDIR = ${MY_INSTALL_LIBDIR}")
message(VERBOSE "MY_INSTALL_TSTDIR = ${MY_INSTALL_TSTDIR}")

#---------------------------------------------------------------------
# Add Directories
#---------------------------------------------------------------------
#
# This structure is a bit frustrating
# Bison needs to create files within the include directory
# so it needs to exist but adding it through CMake drops
# a couple CMake files into it which are unnecessary
# for the end user.
#
add_subdirectory(include)
add_subdirectory(src)


if(BUILD_TESTING)
  include(CTest)
  add_subdirectory(test)
endif()

