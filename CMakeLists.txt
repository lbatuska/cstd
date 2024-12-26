cmake_minimum_required(VERSION 3.5)

project(cstd LANGUAGES C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_STANDALONE "Build cstd as a standalone executable" OFF)

file(GLOB_RECURSE STD_SRC CONFIGURE_DEPENDS "src/*.c")

include_directories(include)

add_library(cstd STATIC ${STD_SRC})

target_include_directories(cstd
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include> # For installed projects
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/private
)

if(CMAKE_BUILD_TYPE MATCHES Debug)
  target_compile_definitions(cstd PRIVATE -DDEBUG)
endif()

if(BUILD_STANDALONE)
  message(STATUS "Building standalone executable")
  add_executable(cstd_exe main.c)
  target_link_libraries(cstd_exe PRIVATE cstd)
endif()

# Export targets for use in other projects
export(TARGETS cstd FILE "${CMAKE_CURRENT_BINARY_DIR}/cstdTargets.cmake")
