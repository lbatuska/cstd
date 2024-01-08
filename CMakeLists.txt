cmake_minimum_required(VERSION 3.5)

project(cstd LANGUAGES C)

file(GLOB STD_SRC CONFIGURE_DEPENDS
     #"std/include/*.h"
     "std/*.c"
)
include_directories("std/include")


add_executable(cstd main.c ${STD_SRC})


install(TARGETS cstd RUNTIME DESTINATION bin)
