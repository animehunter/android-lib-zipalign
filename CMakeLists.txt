project(zipalign)
cmake_minimum_required(VERSION 2.8)

find_package( ZLIB REQUIRED)
if( ZLIB_FOUND )
    include_directories( ${ZLIB_INCLUDE_DIRS} )
    message(STATUS "Found Zlib")
endif( ZLIB_FOUND )

#TODO make this line cross-platform
if(WIN32)
add_definitions(-DHAVE_MS_C_RUNTIME=1)
add_definitions(-DHAVE_WIN32_THREADS=1)
add_definitions(-DHAVE_OFF64_T=1)
add_definitions(-DHAVE_WIN32_FILEMAP=1)
add_definitions(-DOS_PATH_SEPARATOR=92) #ascii code for \ (backslash)
add_definitions(-DHAVE_WINSOCK=1)
endif(WIN32)

if(UNIX)
add_definitions(-DHAVE_PTHREADS=1)
add_definitions(-DHAVE_OFF64_T=1) #might cause problem on older systems!
add_definitions(-DOS_PATH_SEPARATOR=47) #ascii code for / (slash)
add_definitions(-DHAVE_SYS_SOCKET_H=1)
endif(UNIX)

#TODO any other platforms to handle?

add_definitions(-DANDROID_SMP=1) #always needed? (Required by SharedBuffer.cpp/atomic.h)

#Set some C/C++ compile flags
set(CMAKE_C_FLAGS_DEBUG "-ggdb")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb")
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
if(MINGW)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -static-libgcc -static-libstdc++")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -static-libgcc")
endif(MINGW)

include_directories(android/core/include)
include_directories(android/base/include)
include_directories(android/native/include)

aux_source_directory(. SRC_LIST)
aux_source_directory(zipalign SRC_ZIPALIGN)
aux_source_directory(android/native/src/utils SRC_NATIVE_UTILS)
aux_source_directory(android/core/src/libcutils SRC_CORE_CUTILS)

add_library(${PROJECT_NAME} STATIC ${SRC_LIST}
               ${SRC_ZIPALIGN}
               ${SRC_NATIVE_UTILS}
               ${SRC_CORE_CUTILS}
              )

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES include/zipalign.h DESTINATION include)
