cmake_minimum_required(VERSION 3.0.2)
set_property (GLOBAL PROPERTY USE_FOLDERS ON)
project(Workbench)

include(cmake/useful_functions.cmake)

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

# Configure WinSDK
if (WIN32)
    if(${ARCH_64})
        set (WINSDK_DIR ${3RDPARTY_DIR}/_unpack/WindowsKits/8.0/Lib/win8/um/x64)
    else()
        set (WINSDK_DIR ${3RDPARTY_DIR}/_unpack/WindowsKits/8.0/Lib/win8/um/x86)
    endif()
    set (CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${WINSDK_DIR})
endif()


# Set global build variables
set (ROOT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

# Set output folder
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add projects
add_subdirectory(3rdParty)
add_subdirectory(Log)

# Set additional targets' flags
set_target_properties(gtest         PROPERTIES COMPILE_FLAGS -DGTEST_HAS_TR1_TUPLE=0)