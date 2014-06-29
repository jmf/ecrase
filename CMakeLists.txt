cmake_minimum_required(VERSION 2.6)

project(ecrase)

#Don't forget to upgrade
set(VERSION_MAJOR 0) #Major Version
set(VERSION_MINOR 0) #Minor Version
set(VERSION_PATCH 1) #Patchlevel
set(VERSION_EXTRA "unstable") #Extra information for special versions

if(VERSION_EXTRA)
	set(VERSION_PATCH ${VERSION_PATCH}-${VERSION_EXTRA})
else()
	set(VERSION_PATCH ${VERSION_PATCH}-indev) #Disable in release
endif()

set(VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

MESSAGE("Now building ${VERSION_STRING} ...")

SET(CMAKE_MODULE_PATH "${ecrase_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")

file(
        GLOB_RECURSE
        source_files
        src/*
)

file(
        GLOB_RECURSE
        data_files
        data/*
)

if (WIN32)
        set(CMAKE_RC_COMPILE_OBJECT "${CMAKE_RC_COMPILER} -i <SOURCE> -o <OBJECT> -O coff")
        set(source_files icon.rc ${source_files})
endif()

FIND_PACKAGE(SDL2 REQUIRED)
FIND_PACKAGE(SDL2_image REQUIRED)

link_libraries(
   ${SDL2_LIBRARY} 
   ${SDL2_IMAGE_LIBRARY}
)

add_executable(
        ecrase
        ${source_files}
)

