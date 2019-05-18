cmake_minimum_required(VERSION 2.8)
project(carr_unit_tests)

include( CTest )
#enable_testing()

if (TEST_INSTALL)
  include_directories(${CMAKE_INSTALL_PREFIX}/include)
  link_directories(${CMAKE_INSTALL_PREFIX}/lib)
else()
  include_directories(${CMAKE_SOURCE_DIR}/src)
  link_directories(${CMAKE_BINARY_DIR}/src)
endif()

link_libraries(carr)

add_executable(test1 test1.c)
add_test(NAME test1 COMMAND test1)

add_executable(test2 test2.c)
add_test(NAME test2 COMMAND test2)
