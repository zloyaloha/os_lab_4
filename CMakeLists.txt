cmake_minimum_required(VERSION 3.17)
project(os_lab_4 DESCRIPTION "laboratory work on course OS")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(lib1 SHARED ${SOURCE_DIR}/gcf-pi1.c)
add_library(lib2 SHARED ${SOURCE_DIR}/gcf-pi2.c)

target_include_directories(lib1 PUBLIC include)
target_include_directories(lib2 PUBLIC include)

add_executable(${PROJECT_NAME}_static-main.exe ${SOURCE_DIR}/static-main.cpp)
add_executable(${PROJECT_NAME}_dynamic-main.exe ${SOURCE_DIR}/dynamic-main.cpp)

target_link_libraries(${PROJECT_NAME}_static-main.exe PRIVATE lib1)
target_include_directories(${PROJECT_NAME}_dynamic-main.exe PRIVATE include)