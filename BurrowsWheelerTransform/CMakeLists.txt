cmake_minimum_required(VERSION 3.10)

project(BurrowsWheelerTransform VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(INPUT_FILES "${CMAKE_CURRENT_SOURCE_DIR}/input")
set(OUTPUT_FILES "${CMAKE_CURRENT_SOURCE_DIR}/output")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/includes/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/includes/config.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)

set(SOURCES
    src/Main.cpp
    src/BWT.cpp
)

set(HEADER_FILES
    includes/BWT.h
    includes/config.h
)

add_executable(BurrowsWheelerTransform ${SOURCES} ${HEADER_FILES})

if (WIN32)
    message("Compiling on Windows")
    add_compile_definitions(WINDOWS)
    if (MSVC)
        message("Compiling with Microsoft Visual Studio")
        add_compile_definitions(VISUAL_STUDIO)
    endif()
elseif (UNIX)
    message("Compiling on Unix-based OS")
    add_compile_definitions(UNIXOS)
elseif (APPLE)
    message("Compiling on macOS")
    add_compile_definitions(MACOS)
endif()
