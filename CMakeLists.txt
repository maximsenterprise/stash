cmake_minimum_required(VERSION 3.15)
project(Stash)

set(CMAKE_CXX_STANDARD 20)

find_package(CURL REQUIRED)

# Specify C++ resources. Mainly Aether and Flux.
file(GLOB_RECURSE FLUX_SOURCES "${CMAKE_SOURCE_DIR}/stash/flux/*.cpp")
file(GLOB_RECURSE CONVEX_SOURCES "${CMAKE_SOURCE_DIR}/stash/convex/*.cpp")
file(GLOB_RECURSE TESTBIN_SOURCES "${CMAKE_SOURCE_DIR}/test/*.cpp")
file(GLOB_RECURSE UTIL_SOURCES "${CMAKE_SOURCE_DIR}/stash/utils/*.cpp")

include_directories(
    ${CMAKE_SOURCE_DIR}/include 
    ${CMAKE_SOURCE_DIR}/lib
)

set(SOURCES
    ${FLUX_SOURCES}
    ${TESTBIN_SOURCES}
    ${CONVEX_SOURCES}
    ${UTIL_SOURCES}
)

if(APPLE)
    # Specify Objective-C++ resources. Mainly for rendering.
    file(GLOB_RECURSE OBJCXX_SOURCES "${CMAKE_SOURCE_DIR}/macOS/*.mm")
    
    # Add to executable 
    list(APPEND SOURCES ${OBJCXX_SOURCES}) 

    # Set compiler to Objective-C++ for macOS 
    set_source_files_properties(${OBJC_SOURCES} PROPERTIES
        COMPILE_FLAGS "-x objective-c++"  # Make use of Objective-C++ compiler
    ) 
endif()

add_executable(stashtest ${SOURCES})
set_target_properties(stashtest PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")

target_link_libraries(stashtest ${CURL_LIBRARIES})

if(APPLE)
    target_link_libraries(stashtest
        "-framework AppKit"
        "-framework SwiftUI"
    )
endif()
