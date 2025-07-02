cmake_minimum_required(VERSION 3.10)
project(Calculator)  

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

add_executable(calculator calculator.c)
target_include_directories(calculator PRIVATE ${GTK3_INCLUDE_DIRS})
target_link_libraries(calculator ${GTK3_LIBRARIES})
