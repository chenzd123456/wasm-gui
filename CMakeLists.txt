cmake_minimum_required(VERSION 3.14)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

set (WAMR_BUILD_INTERP 0)
set (WAMR_BUILD_AOT 1)
set (WAMR_BUILD_JIT 0)
set (WAMR_BUILD_LIB_PTHREAD 0)
set (WAMR_BUILD_DUMP_CALL_STACK 0)
set (WAMR_BUILD_LIBC_WASI 0)
set (WAMR_BUILD_LIBC_BUILTIN 0)
set (WAMR_BUILD_FAST_INTERP 0)
set (WAMR_BUILD_MULTI_MODULE 1)
set (WAMR_BUILD_SIMD 0)

add_subdirectory(3rd/wasm-micro-runtime)

project(Host C)

set (CMAKE_C_STANDARD 99)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/3rd/wasm-micro-runtime/core/iwasm/include
)

file(GLOB_RECURSE SOURCE
    ${CMAKE_SOURCE_DIR}/src/*.c
)

add_executable(${PROJECT_NAME} ${SOURCE})

if (APPLE)
  target_link_libraries (${PROJECT_NAME}  iwasm_static -lm -ldl -lpthread)
else ()
  target_link_libraries (${PROJECT_NAME}  iwasm_static -lm -ldl -lpthread -lrt)
endif ()