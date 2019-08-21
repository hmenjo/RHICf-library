cmake_minimum_required(VERSION 2.8)

project(converter)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} $ENV{ROOTSYS}/etc/cmake)

#If absolute path is needed in CCJ, please uncomment the following lines
#list(APPEND CMAKE_PREFIX_PATH /ccj/w/r01/RHICf/linux5/opt/root_v5.34.36)
#set(CMAKE_MODULE_PATH /ccj/w/r01/RHICf/linux5/opt/root_v5.34.36/etc/cmake ${CMAKE_MODULE_PATH})

find_package(ROOT REQUIRED COMPONENTS RIO Net)
message("PATH(CMAKE) : ${CMAKE_MODULE_PATH}")
message("PATH(ROOT)  : ${ROOT_LIBRARIES}")

file(GLOB sources 
			 ${PROJECT_SOURCE_DIR}/suzukilib/*.cpp 
			 ${PROJECT_SOURCE_DIR}/src/*.cc 
			 ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers 
			 ${PROJECT_SOURCE_DIR}/suzukilib/*.hpp 
			 ${PROJECT_SOURCE_DIR}/include/*.h )

add_executable(convertor convertor.cc ${sources} ${headers})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/../Library/include)
include_directories(${PROJECT_SOURCE_DIR}/../general/dict/include)
include_directories(${PROJECT_SOURCE_DIR}/suzukilib/)
include_directories(${ROOT_INCLUDE_DIR})

set(libraries 	${PROJECT_SOURCE_DIR}/suzukilib/libsuzukiEvent.so
					${PROJECT_SOURCE_DIR}/../Library/lib/libRHICf.so
					${PROJECT_SOURCE_DIR}/../general/dict/lib/libLHCfEvent.so)

target_link_libraries(convertor ${libraries} ${ROOT_LIBRARIES})

