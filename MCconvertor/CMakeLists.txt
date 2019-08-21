cmake_minimum_required(VERSION 2.8)

project(converter)
#list(APPEND CMAKE_PREFIX_PATH /ccj/w/r01/satoken/src/root_v5.34.36_build2)

list(APPEND CMAKE_PREFIX_PATH /ccj/w/r01/RHICf/linux5/opt/root_v5.34.36)
set(CMAKE_MODULE_PATH /ccj/w/r01/RHICf/linux5/opt/root_v5.34.36/etc/cmake ${CMAKE_MODULE_PATH})

#list(APPEND CMAKE_PREFIX_PATH /ccj/w/r01/satoken/src/root_v5.34.36)
#set(CMAKE_MODULE_PATH /ccj/w/r01/satoken/src/root_v5.34.36/etc/cmake ${CMAKE_MODULE_PATH})

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} /ccj/w/r01/satoken/src/root_v5.34.36/etc/cmake)
message("Watch CMAKE_MODULE_PATH : ${CMAKE_MODULE_PATH}")

find_package(ROOT REQUIRED COMPONENTS RIO Net)

#find_package(ROOT)
#find_library(M_LIB m)
#message("Watch thi: ${ROOT_LIBRARIES}")

set(PROJECT_SOURCE_DIR /ccj/u/satoken/RHICf/convertor)

file(GLOB sources ${PROJECT_SOURCE_DIR}/suzukilib/*.cpp ${PROJECT_SOURCE_DIR}/src/*.cc ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/rhicflib/src/*.cpp ${PROJECT_SOURCE_DIR}/lhcflib/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/suzukilib/*.hpp ${ROOT_INCLUDE_DIR}/*.hh ${ROOT_INCLUDE_DIR}/*.h ${PROJECT_SOURCE_DIR}/include/*.h ${PROJECT_SOURCE_DIR}/rhicflib/include/*.h ${PROJECT_SOURCE_DIR}/lhcflib/include/*.h)
#file(GLOB libraries $ENV{ROOTSYS}/lib/*.so)
file(GLOB libraries ${ROOTSYS}/lib/root/*.so)


add_executable(convertor convertor.cc ${sources} ${headers})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/rhicflib/include)
include_directories(${PROJECT_SOURCE_DIR}/lhcflib/include)
include_directories(${PROJECT_SOURCE_DIR}/suzukilib/)
#include_directories(/ccj/u/satoken/RHICf/convertor/include)
#include_directories(/ccj/u/satoken/RHICf/convertor/rhicflib/include)
#include_directories(/ccj/u/satoken/RHICf/convertor/lhcflib/include)
#include_directories(/ccj/u/satoken/RHICf/convertor/suzukilib/)
include_directories(${ROOT_INCLUDE_DIR})



link_directories(/ccj/u/satoken/RHICf/convertor/rhicflib/lib)
link_directories(/ccj/u/satoken/RHICf/convertor/lhcflib/lib)
link_directories(/ccj/u/satoken/RHICf/convertor/suzukilib)

target_link_libraries(convertor ${libraries})
target_link_libraries(convertor ${ROOT_LIBRARIES})

target_link_libraries(convertor ${PROJECT_SOURCE_DIR}/suzukilib/libsuzukiEvent.so)
target_link_libraries(convertor ${PROJECT_SOURCE_DIR}/rhicflib/lib/libRHICfEvent.so)
target_link_libraries(convertor ${PROJECT_SOURCE_DIR}/lhcflib/lib/libLHCfEvent.so)
target_link_libraries(convertor ${ROOTSYS}/lib/root/libEG.so)

