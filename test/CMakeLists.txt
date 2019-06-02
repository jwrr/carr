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

macro(add_tests)
  set(TESTS "${ARGN}")
  foreach(TEST IN LISTS TESTS)
    add_executable(${TEST} ${TEST}.c)
    add_test(NAME  ${TEST} COMMAND ${TEST})
  endforeach()
endmacro()

link_libraries(carr)
add_tests(test1
carr_new_test
carr_init_test
carr_dup_test
carr_copy_test
carr_resize_test
carr_resize_if_needed_test
)

