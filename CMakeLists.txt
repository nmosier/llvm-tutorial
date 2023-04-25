cmake_minimum_required(VERSION 3.10)

project(llvm_tutorial)

set(CMAKE_CXX_STANDARD 17)

find_package(LLVM REQUIRED CONFIG)
include(AddLLVM)

function(llvm_add_library name)
  add_library(${name} ${ARGN})
  target_include_directories(${name} SYSTEM BEFORE PUBLIC ${LLVM_INCLUDE_DIRS})
  target_compile_definitions(${name} PRIVATE ${LLVM_DEFINITIONS})
  if(APPLE)
    target_link_options(${name} PRIVATE -undefined dynamic_lookup)
  endif()
endfunction()

if(APPLE)
  add_link_options(-undefined dynamic_lookup)
endif()

llvm_add_library(simple MODULE simple.cpp)
# llvm_config(simple)
# target_link_libraries(simple PRIVATE LLVM)
