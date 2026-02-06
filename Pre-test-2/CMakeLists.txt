cmake_minimum_required(VERSION 3.10)
project(FibonacciRunner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find WasmEdge automatically 
find_path(WASMEDGE_INCLUDE_DIR 
    NAMES wasmedge/wasmedge.h
    HINTS "C:/Program Files/WasmEdge/include" "$ENV{HOME}/.wasmedge/include" "/usr/local/include"
)
find_library(WASMEDGE_LIB 
    NAMES wasmedge
    HINTS "C:/Program Files/WasmEdge/lib" "$ENV{HOME}/.wasmedge/lib" "/usr/local/lib"
)

# Source File
add_executable(fibonacci_runner fibonacci_runner.cpp)

# Link Libraries
if(WASMEDGE_INCLUDE_DIR AND WASMEDGE_LIB)
    message(STATUS "Found WasmEdge library at: ${WASMEDGE_LIB}")
    target_include_directories(fibonacci_runner PRIVATE ${WASMEDGE_INCLUDE_DIR})
    target_link_libraries(fibonacci_runner PRIVATE ${WASMEDGE_LIB})
else()
    message(WARNING "WasmEdge not found via lookup. Attempting direct link.")
    target_link_libraries(fibonacci_runner wasmedge)
endif()

# Copy fibonacci.wasm to the same folder as the executable
add_custom_command(TARGET fibonacci_runner POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/fibonacci.wasm"
    "$<TARGET_FILE_DIR:fibonacci_runner>"
)