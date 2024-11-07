cmake_minimum_required(VERSION 3.0)
project(Stash)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE FLUX_SOURCES "${CMAKE_SOURCE_DIR}/stash/flux/*.cpp")
file(GLOB_RECURSE TESTBIN_SOURCES "${CMAKE_SOURCE_DIR}/test/*.cpp")

include_directories(
    ${CMAKE_SOURCE_DIR}/include 
)

set(SOURCES
    ${FLUX_SOURCES}
    ${TESTBIN_SOURCES}
)

add_executable(stashtest ${SOURCES})
set_target_properties(stashtest PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
