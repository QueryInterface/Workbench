cmake_minimum_required(VERSION 3.10)
set_property (GLOBAL PROPERTY USE_FOLDERS ON)
project(Workbench)

include(cmake/UtilityFunctions.cmake)

update_compiler_settings()
check_apple_platform()

# Global variables
set(3RDPARTY_DIR ${CMAKE_CURRENT_LIST_DIR}/3rdParty)

if(CMAKE_SIZEOF_VOID_P EQUAL 8) 
    set(ARCH_64 TRUE) 
else() 
    set(ARCH_64 FALSE) 
endif()

if (WIN32)
    set (DYNAMIC_LIB_SUFIX .dll)
    set (STATIC_LIB_SUFIX .lib)
    set (BIN2CPP ${3RDPARTY_DIR}/bin2cpp/bin2cpp.exe)
elseif(APPLE)
    set (DYNAMIC_LIB_SUFIX .dylib)
    set (STATIC_LIB_SUFIX .a)
    set (BIN2CPP ${3RDPARTY_DIR}/bin2cpp/bin2cpp_mac)
else()
    set (DYNAMIC_LIB_SUFIX .so)
    set (STATIC_LIB_SUFIX .a)
    set (BIN2CPP ${3RDPARTY_DIR}/bin2cpp/bin2cpp)
endif()

# Set global build variables
set (ROOT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

# Set output folder
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add projects
add_subdirectory(3rdParty)