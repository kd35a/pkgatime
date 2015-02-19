# CMAKE_C_STANDARD was added in 3.1
cmake_minimum_required (VERSION 3.1 FATAL_ERROR)
project (pkgatime)

# Set compiler flags
set(CMAKE_C_STANDARD "99")

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic" CACHE STRING
    "Flags used by the compiler during all build types."
    FORCE)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
    "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel.")
endif(NOT CMAKE_BUILD_TYPE)

# Libraries
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(alpm REQUIRED)
add_library(slist slist.c)

# Project deliverable and linking
add_executable(pkgatime main.c)
target_link_libraries(pkgatime LINK_PRIVATE slist)
target_link_libraries(pkgatime LINK_PUBLIC alpm)

install(TARGETS pkgatime DESTINATION bin)

# vim:set ts=4 sw=4 et:
