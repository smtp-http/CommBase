PROJECT(commbase)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

#gdb
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

FILE(GLOB SRC_LIST_CPP "${PROJECT_SOURCE_DIR}/src/*.cpp")
FILE(GLOB SRC_LIST_C "${PROJECT_SOURCE_DIR}/src/*.c")

MESSAGE(STATUS "src_list:" ${SRC_LIST_CPP} ${SRC_LIST_C})

SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)

#ADD_LIBRARY(commbase SHARED ${SRC_LIST_CPP} ${SRC_LIST_C})
ADD_LIBRARY(ucom SHARED ${SRC_LIST_CPP} ${SRC_LIST_C})

AUX_SOURCE_DIRECTORY(. DIR_SRCS)
include_directories(src)
include_directories(include)
add_subdirectory(src)
add_subdirectory(test)

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)

ADD_EXECUTABLE(commb ${DIR_SRCS})
TARGET_LINK_LIBRARIES(commb ucom pthread event)
