cmake_minimum_required(VERSION 3.0)
project(Stash)

set(CMAKE_CXX_STANDARD 20)

# Specify C++ resources. Mainly Aether and Flux.
file(GLOB_RECURSE FLUX_SOURCES "${CMAKE_SOURCE_DIR}/stash/flux/*.cpp")
file(GLOB_RECURSE CONVEX_SOURCES "${CMAKE_SOURCE_DIR}/stash/convex/*.cpp")
file(GLOB_RECURSE TESTBIN_SOURCES "${CMAKE_SOURCE_DIR}/test/*.cpp")
file(GLOB_RECURSE UTIL_SOURCES "${CMAKE_SOURCE_DIR}/stash/utils/*.cpp")

include_directories(
    ${CMAKE_SOURCE_DIR}/include 
)

set(SOURCES
    ${FLUX_SOURCES}
    ${TESTBIN_SOURCES}
    ${CONVEX_SOURCES}
    ${UTIL_SOURCES}
)

if(APPLE)
    # Specify Objective-C++ resources. Mainly for rendering.
    file(GLOB_RECURSE OBJC_SOURCES "${CMAKE_SOURCE_DIR}/macOS/render/*.mm")
    
    # Add to executable 
    list(APPEND SOURCES ${OBJC_SOURCES})

    # Set compiler to Objective-C++ for macOS 
    set_source_files_properties(${OBJC_SOURCES} PROPERTIES
        COMPILE_FLAGS "-x objective-c++"  # Make use of Objective-C++ compiler
    )

endif()

add_executable(stashtest ${SOURCES})
set_target_properties(stashtest PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")

if(APPLE)
    target_link_libraries(stashtest
        "-framework AppKit"
    )
endif()
