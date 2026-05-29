cmake_minimum_required(VERSION 3.14)
project(cf-gemm)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Enable PCH support
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-Winvalid-pch" COMPILER_SUPPORTS_PCH)

if(COMPILER_SUPPORTS_PCH)
  message(STATUS "Compiler supports PCH")
else()
  message(FATAL_ERROR "Your compiler does not support PCH.")
endif()





# Build the cf-gemm library
add_library(cf-gemm
    src/gemm.cpp
)
target_include_directories(cf-gemm PUBLIC ${CMAKE_SOURCE_DIR}/include)





add_executable(main src/main.cpp)
target_compile_options(main PRIVATE -O1 -march=native)  # O1 for better benchmarking, -march=native for intrinsics
target_link_libraries(main cf-gemm)

# Enable intrinsics (SSE/AVX) if needed
if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(cf-gemm PRIVATE -march=native)
elseif(MSVC)
    target_compile_options(cf-gemm PRIVATE /arch:AVX)
endif()



