cmake_minimum_required(VERSION 3.15)
project(VevingHjelper VERSION 1.0 LANGUAGES CXX)

# use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -----------------------------------------------------------------------------
# Add raylib as a subproject.  The repository already contains the raylib
# sources under `external/raylib`.  Its own CMakeLists.txt will configure a
# `raylib` target that we can link against.  This allows cloning the project on
# Windows (and other platforms) without needing a prebuilt raylib library.
# -----------------------------------------------------------------------------
add_subdirectory(external/raylib)

# -----------------------------------------------------------------------------
# Application target
# -----------------------------------------------------------------------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE APP_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(VevingHjelper ${APP_SOURCES})

# link against raylib and any platform-specific libraries it requires
target_link_libraries(VevingHjelper PUBLIC raylib)

if(APPLE)
    # macOS frameworks already handled by raylib but keep here for clarity
    find_library(COCOA_FRAMEWORK Cocoa)
    find_library(IOKIT_FRAMEWORK IOKit)
    find_library(COREVIDEO_FRAMEWORK CoreVideo)
    target_link_libraries(VevingHjelper PRIVATE ${COCOA_FRAMEWORK}
                                           ${IOKIT_FRAMEWORK}
                                           ${COREVIDEO_FRAMEWORK})
elseif(WIN32)
    # on Windows raylib needs the OpenGL library
    target_link_libraries(VevingHjelper PRIVATE opengl32)
endif()

# -----------------------------------------------------------------------------
# Unit tests (Catch2)
# -----------------------------------------------------------------------------
add_executable(tests
    tests/test.cpp
)

target_include_directories(tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/catch
)

enable_testing()
add_test(NAME simple_test COMMAND tests)
