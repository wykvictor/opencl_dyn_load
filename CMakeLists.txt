cmake_minimum_required(VERSION 2.6)
project(Opencl-dyn-load)

option(USE_OPENCL "Use OpenCL, default to true" 1)
if (USE_OPENCL)
  set(OPENCL_FOUND 1)
  add_definitions(-DHAVE_OPENCL)
endif()

file(GLOB SOURCE_FILES "opencl_dyn_load.cpp")

add_executable(main main.cpp ${SOURCE_FILES})
