# cmake .. -DBUILD_TESTING=ON
# make
# cd test
# ctest --output-on-failure

cmake_minimum_required(VERSION 2.8)
project(carr_prj)
set (CMAKE_BUILD_TYPE Debug)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Default install path" FORCE)
endif()

add_subdirectory(src)

option(BUILD_TESTING "" OFF)
if (BUILD_TESTING)
  add_subdirectory(test)
endif()


