cmake_minimum_required(VERSION 3.5)

project(iota_common)

enable_language(C)
enable_testing()

# Kerl Optimization options
option(KERL_REF_64 "Kerl reference 64bit" ON)
option(KERL_REF_32 "Kerl reference 32bit" OFF)
option(KERL_AsmX86_64 "Kerl optimized AsmX86-64" OFF)
option(KERL_COMPACT "Kerl minimizing code and memory sizes for 64bit" OFF)
option(KERL_AVX2 "Kerl with AVX2 instruction set optimization" OFF)
option(KERL_INPLACE_32 "Kerl minimizing memory sizes for 32bit" OFF)
option(KERL_64u6 "Kerl for 64-bit platforms with 6 rounds unrolled" OFF)
option(KERL_64uf "Kerl for 64-bit platforms with full rounds unrolled" OFF)
option(KERL_T2o1 "Kerl calls Keccak-p[1600] twice" OFF)
option(KERL_T4o1 "Kerl calls Keccak-p[1600] four times" OFF)
option(KERL_T8o1 "Kerl calls Keccak-p[1600] eight times" OFF)
option(KERL_T4o2 "Kerl calls Keccak-p[1600]x2 twice" OFF)
option(KERL_T8o2 "Kerl calls Keccak-p[1600]x2 four times" OFF)
option(KERL_T8o4 "Kerl calls Keccak-p[1600]x4 twice" OFF)

# Kerl times 2 SIMD
option(KERL_SIMD128_SSE2u2 "Kerl SSE2 instruction set, with two rounds unrolled" OFF)
option(KERL_SIMD128_SSE2uf "Kerl SSE2 instruction set, with all rounds unrolled" OFF)
# Kerl times 4 SIMD
option(KERL_SIMD256_AVX2u6 "Kerl AVX2 instruction set, with 6 rounds unrolled" OFF)
option(KERL_SIMD256_AVX2u12 "Kerl AVX2 instruction set, with 12 rounds unrolled" OFF)
option(KERL_SIMD256_AVX2uf "Kerl AVX2 instruction set, with all rounds unrolled" OFF)

# Kerl ARM Optimization
option(KERL_INPLACE_ARMv6M "Kerl minimizing memory sizes for ARMv6M" OFF)
option(KERL_INPLACE_ARMv7M "Kerl minimizing memory sizes for ARMv7M" OFF)
option(KERL_INPLACE_ARMv7A "Kerl minimizing memory sizes for ARMv7A" OFF)
option(KERL_ARMv7A_ASM "Kerl neon optimiaztion for ARMv7A" OFF)
option(KERL_ARMv8A_ASM "Kerl neon optimiaztion for ARMv8A" OFF)

include(ExternalProject)
link_directories("${CMAKE_INSTALL_PREFIX}/lib")

include(cmake/keccak.cmake)

# for unit test
include(cmake/unity.cmake)


set(IOTA_COMMON_EXTERNAL_HEADERS 
  "${PROJECT_BINARY_DIR}/include"
  "${PROJECT_BINARY_DIR}/include/keccak"
)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(benchmarks)
