
cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(cstd LANGUAGES C)

set(CMAKE_C_STANDARD 11)

file(GLOB STD_SRC CONFIGURE_DEPENDS "include/*.c")
include_directories("include")

add_executable(cstd main.c ${STD_SRC})

if(CMAKE_BUILD_TYPE MATCHES Debug)
  add_definitions(-DDEBUG)
endif()
