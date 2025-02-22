cmake_minimum_required(VERSION 2.8)
project(sherry)

include (./cmake/utils.cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined")

include_directories(.)
include_directories(/build/yaml-cpp-0.8.0/include)
link_directories(/apps/sherry/lib)

find_library(YAMLCPP libyaml-cpp.a)

set(LIB_SRC
    sherry/address.cc
    sherry/bytearray.cc
    sherry/log.cc
    sherry/fd_manager.cc
    sherry/fiber.cc
    sherry/util.cc
    sherry/hook.cc
    sherry/scheduler.cc
    sherry/socket.cc
    sherry/timer.cc
    sherry/config.cc
    sherry/thread.cc
    sherry/iomanager.cc
    )

add_library(sherry SHARED ${LIB_SRC})
force_redefine_file_macro_for_sources(sherry)  #__FILE__
#add_library(sherry_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES (sherry_static PROPERTIES OUTPUT_NAME "sherry")

find_library(YAMLCPP yaml-cpp)
find_library(PTHREAD pthread)
#set(LIBS, ${LIBS} sherry)
#set(LIBS, ${LIBS} dl)
#set(LIBS, ${LIBS} ${YAMLCPP})
#set(LIBS, ${LIBS} ${PTHREAD})

set(LIBS
    sherry
    dl
    pthread
    yaml-cpp
    )

message("***", ${LIBS})
add_executable(test tests/test.cc)
add_dependencies(test sherry)
force_redefine_file_macro_for_sources(test)  #__FILE__
target_link_libraries(test ${LIBS})

add_executable(test_config tests/test_config.cc)
add_dependencies(test_config sherry)
force_redefine_file_macro_for_sources(test_config)  #__FILE__
target_link_libraries(test_config ${LIBS})

add_executable(test_thread tests/test_thread.cc)
add_dependencies(test_thread sherry)
force_redefine_file_macro_for_sources(test_thread)  #__FILE__
target_link_libraries(test_thread ${LIBS})

add_executable(test_util tests/test_util.cc)
add_dependencies(test_util sherry)
force_redefine_file_macro_for_sources(test_util)  #__FILE__
target_link_libraries(test_util ${LIBS})

add_executable(test_fiber tests/test_fiber.cc)
add_dependencies(test_fiber sherry)
force_redefine_file_macro_for_sources(test_fiber)  #__FILE__
target_link_libraries(test_fiber ${LIBS})

add_executable(test_scheduler tests/test_scheduler.cc)
add_dependencies(test_scheduler sherry)
force_redefine_file_macro_for_sources(test_scheduler)  #__FILE__
target_link_libraries(test_scheduler ${LIBS})

add_executable(test_iomanager tests/test_iomanager.cc)
add_dependencies(test_iomanager sherry)
force_redefine_file_macro_for_sources(test_iomanager)  #__FILE__
target_link_libraries(test_iomanager ${LIBS})

add_executable(test_hook tests/test_hook.cc)
add_dependencies(test_hook sherry)
force_redefine_file_macro_for_sources(test_hook)  #__FILE__
target_link_libraries(test_hook ${LIBS})

add_executable(test_address tests/test_address.cc)
add_dependencies(test_address sherry)
force_redefine_file_macro_for_sources(test_address)  #__FILE__
target_link_libraries(test_address ${LIBS})

add_executable(test_socket tests/test_socket.cc)
add_dependencies(test_socket sherry)
force_redefine_file_macro_for_sources(test_socket)  #__FILE__
target_link_libraries(test_socket ${LIBS})

add_executable(test_bytearray tests/test_bytearray.cc)
add_dependencies(test_bytearray sherry)
force_redefine_file_macro_for_sources(test_bytearray)  #__FILE__
target_link_libraries(test_bytearray ${LIBS})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)