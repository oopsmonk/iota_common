cmake_minimum_required(VERSION 3.5)

project(iota_common)

enable_language(C)
enable_testing()

option(ENABLE_ASAN "Enable Address sanitizer" ON)
option(COMMON_TESTS "Enable unit tests" ON)
option(COMMON_BENCH "Enable benchmarks" OFF)

include(ExternalProject)
link_directories("${CMAKE_INSTALL_PREFIX}/lib")

# for unit test
include(cmake/unity.cmake)

include(cmake/uthash.cmake)
include(cmake/base58.cmake)
include(cmake/libsodium.cmake)

if(ENABLE_ASAN)
  include(cmake/asan.cmake)
endif()


set(IOTA_COMMON_EXTERNAL_HEADERS 
  "${CMAKE_INSTALL_PREFIX}/include"
)

add_subdirectory(src)

if(COMMON_TESTS)
  add_subdirectory(tests)
endif()
if(COMMON_BENCH)
  add_subdirectory(benchmarks)
endif()
