#
# Master AtomSpace Computer Vision Types CMake file
#
# General organization:
# -- check for different compilers, OS'es
# -- search for various required & optional libraries/tools
# -- decide what to build based on above results.
# -- configure various config files.
# -- print pretty summary
#

# Require "modern" CMake
cmake_minimum_required(VERSION 3.12)

project(atomspace-vision)

# default build type
if (CMAKE_BUILD_TYPE STREQUAL "")
	set(CMAKE_BUILD_TYPE Release)
endif (CMAKE_BUILD_TYPE STREQUAL "")

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# add_definitions(-DPROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
#                 -DPROJECT_BINARY_DIR="${CMAKE_BINARY_DIR}")

# ===============================================================
# Check for existance of various required, optional packages.
# Listed in alphabetical order, more or less.
# CogUtil must come first, because it supplies various FindXXX macros.

# Add the 'lib' dir to cmake's module search path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/lib/")

# Cogutil
find_package(CogUtil 2.0.1 REQUIRED)
if (COGUTIL_FOUND)
    message(STATUS "CogUtil found.")
    # add_definitions(-DHAVE_COGUTIL)
    # set(HAVE_COGUTIL 1)
else (COGUTIL_FOUND)
    message(FATAL_ERROR "CogUtil missing: it is needed!")
endif (COGUTIL_FOUND)

# add the 'cmake' directory from cogutil to search path
list(APPEND CMAKE_MODULE_PATH  ${COGUTIL_DATA_DIR}/cmake)

include(OpenCogGccOptions)
include(OpenCogLibOptions)
include(OpenCogInstallOptions)
include(Summary)

# ===================================================================
# Check for existance of various required, optional packages.

# AtomSpace
find_package(AtomSpace 5.0.3 REQUIRED)
if (ATOMSPACE_FOUND)
	message(STATUS "AtomSpace found.")
	# add_definitions(-DHAVE_ATOMSPACE)
	# set(HAVE_ATOMSPACE 1)
else (ATOMSPACE_FOUND)
	message(FATAL_ERROR "AtomSpace missing: it is needed!")
endif (ATOMSPACE_FOUND)

# OpenCV
find_package(OpenCV REQUIRED)

# ----------------------------------------------------------
# Needed for unit tests

find_package(Catch2 QUIET)
if (NOT Catch2_FOUND)
	message(STATUS "Catch2 missing: needed for unit tests.")
endif (NOT Catch2_FOUND)

# ----------------------------------------------------------
# Guile Python and Cython

include(OpenCogFindGuile)
include(OpenCogFindPython)

# ----------------------------------------------------------
# Optional, currently needed only to hush up DRD in util/Logger.cc
# find_package(VALGRIND)
# if (VALGRIND_FOUND)
# 	message(STATUS "VALGRIND was found.")
# 	if (VALGRIND_INCLUDE_DIR)
# 		message(STATUS "VALGRIND devel headers found.")
# 		add_definitions(-DHAVE_VALGRIND)
# 	else (VALGRIND_INCLUDE_DIR)
# 		message(STATUS "VALGRIND devel headers NOT FOUND: needed for thread debugging.")
# 	endif (VALGRIND_INCLUDE_DIR)
# else (VALGRIND_FOUND)
# 	message(STATUS "VALGRIND missing: needed for thread debugging.")
# endif (VALGRIND_FOUND)

# ===================================================================
# Include configuration.

# Set default include paths.
# include_directories(${PROJECT_SOURCE_DIR}
# 	${COGUTIL_INCLUDE_DIR} ${ATOMSPACE_INCLUDE_DIR})

# Macros that define how atom types get declared.
if (NOT DEFINED ATOMSPACE_DATA_DIR)
	set (ATOMSPACE_DATA_DIR "${COGUTIL_DATA_DIR}")
endif (NOT DEFINED ATOMSPACE_DATA_DIR)

include("${ATOMSPACE_DATA_DIR}/cmake/OpenCogMacros.cmake")
include("${ATOMSPACE_DATA_DIR}/cmake/OpenCogGuile.cmake")
include("${ATOMSPACE_DATA_DIR}/cmake/OpenCogCython.cmake")

# ==========================================================
# Decide what to build, based on the packages found.

# Basic paths
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/opencog)
set(VISION_CMAKE_CONFIG_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/AtomSpaceVision)

add_subdirectory(lib)
add_subdirectory(opencog)

# if (CXXTEST_FOUND)
# 	add_custom_target(tests)
# 	add_subdirectory(tests EXCLUDE_FROM_ALL)
# 	if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
# 		# doing coverage stuff while running tests if this is the Coverage build
# 		add_custom_target(test
# 			# TODO lcov should be found by cmake first
# 			# TODO set it up so that we can pick to run coverage per test, or
# 			# combined across all tests (the latter is MUCH faster). Use a define?
# 			# There is coverage specific stuff in AddCxxTest.cmake now...
# 			WORKING_DIRECTORY tests
# 			COMMAND ${CMAKE_CTEST_COMMAND} --force-new-ctest-process --output-on-failure $(ARGS)

# 			# This script combines the coverage analysis of each test,
# 			# then creates html in tests/lcov
# 			# Note: this should now be run separately...
# 			#COMMAND ${PROJECT_SOURCE_DIR}/scripts/combine_lcov.sh
# 			COMMENT "Running tests with coverage..."
# 		)
# 	else (CMAKE_BUILD_TYPE STREQUAL "Coverage")
# 		# if this is a build with coverage enabled then test normally
# 		add_custom_target(test
# 			DEPENDS tests
# 			WORKING_DIRECTORY tests
# 			COMMAND ${CMAKE_CTEST_COMMAND} --force-new-ctest-process --output-on-failure $(ARGS)
# 			COMMENT "Running tests..."
# 		)
# 	endif (CMAKE_BUILD_TYPE STREQUAL "Coverage")
# endif (CXXTEST_FOUND)

# set(CMAKE_CXX_CLANG_TIDY "clang-tidy")

add_custom_target(cscope
	COMMAND find opencog examples tests -name '*.cc' -o -name '*.h' -o -name '*.cxxtest' -o -name '*.scm' > ${CMAKE_SOURCE_DIR}/cscope.files
	COMMAND cscope -b
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	COMMENT "Generating CScope database"
)

# ===================================================================
# documentation
find_package(Doxygen)
# add_subdirectory(doc EXCLUDE_FROM_ALL)

# ===================================================================
# Show a summary of what we found, what we will do.

summary_add("AtomSpace Vision" "AtomSpace Computer Vision Types" ATOMSPACE_FOUND)
summary_add("Doxygen" "Code documentation" DOXYGEN_FOUND)
summary_add("Unit tests" "Unit tests" Catch2_FOUND)

summary_show()
