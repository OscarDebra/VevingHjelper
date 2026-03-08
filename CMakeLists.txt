cmake_minimum_required(VERSION 3.15)
project(VevingHjelper VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(external/raylib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE APP_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(VevingHjelper ${APP_SOURCES})

target_link_libraries(VevingHjelper PUBLIC raylib)

if(APPLE)
    find_library(COCOA_FRAMEWORK Cocoa)
    find_library(IOKIT_FRAMEWORK IOKit)
    find_library(COREVIDEO_FRAMEWORK CoreVideo)
    target_link_libraries(VevingHjelper PRIVATE ${COCOA_FRAMEWORK}
                                           ${IOKIT_FRAMEWORK}
                                           ${COREVIDEO_FRAMEWORK})
elseif(WIN32)
    target_link_libraries(VevingHjelper PRIVATE opengl32)
endif()