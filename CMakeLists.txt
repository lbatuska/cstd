cmake_minimum_required(VERSION 3.5)
add_compile_options(-Wno-incompatible-pointer-types)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(cstd LANGUAGES C)

set(CMAKE_C_STANDARD 11)


file(GLOB STD_SRC CONFIGURE_DEPENDS
     "std/*.c"
)
include_directories("std/include")


add_executable(cstd main.c ${STD_SRC})


install(TARGETS cstd RUNTIME DESTINATION bin)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif()
