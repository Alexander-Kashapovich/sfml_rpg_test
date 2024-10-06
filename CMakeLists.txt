cmake_minimum_required(VERSION 3.12.0)


project(sfml_test)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(SRC_DIR "src")
file(GLOB_RECURSE SRC_CPP "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE SRC_H "${SRC_DIR}/*.h")


set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/SFML-2.6.1/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS system window graphics audio network REQUIRED)

include_directories("${CMAKE_SOURCE_DIR}/SFML-2.6.1/include")
include_directories("${SRC_DIR}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/libs/")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Main ${SRC_CPP} ${SRC_H})

target_link_libraries(Main
 sfml-system
 sfml-window
 sfml-graphics 
 sfml-audio
 sfml-network
 mingw32
 psapi
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
set_target_properties(Main PROPERTIES LINK_FLAGS "-pg")
endif()

