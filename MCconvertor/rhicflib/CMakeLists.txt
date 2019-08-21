cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(RHICflib)

find_package(ROOT)
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)
#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS RIO Net)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
ROOT_GENERATE_DICTIONARY(G__RHICfEvent ${headers} LINKDEF LinkDef.h)

#---Create a shared library with geneated dictionary
add_library(RHICfEvent SHARED ${sources} G__RHICfEvent.cxx)
target_link_libraries(RHICfEvent ${ROOT_LIBRARIES})

#---Create  a main program using the library
#add_executable(Main MainEvent.cxx)
#target_link_libraries(Main Event)
