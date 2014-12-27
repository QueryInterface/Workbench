cmake_minimum_required(VERSION 3.0.2)
update_compiler_settings()

# Form binaries
add_library(Log STATIC
    Log.h
    Log.cpp
    )

include_directories(Log ${ROOT_DIRECTORY}/Utils)