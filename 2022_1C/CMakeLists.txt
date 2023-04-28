cmake_minimum_required(VERSION 3.14.0)
project(gcj_end_bp)

# ninja and makefile generators only.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

foreach(NUM RANGE 1 5)
  set(CUR_NAME "task${NUM}")
  add_executable(${CUR_NAME} ${CUR_NAME}.cpp)
  target_compile_definitions(${CUR_NAME} PRIVATE DEBUG_HACK)
  target_include_directories(${CUR_NAME} PRIVATE include)
endforeach()
