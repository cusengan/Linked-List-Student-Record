cmake_minimum_required(VERSION 2.6)

set(CMAKE_C_FLAGS "-g -std=c89 -pedantic")

add_library(student STATIC StudentRecordNode.c StudentRecord.c)


add_executable(homework6 1001227439_wxt_homework6.c)

target_link_libraries(homework6 student)

