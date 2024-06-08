cmake_minimum_required(VERSION 3.5)

project(testproject)

set(CMAKE_CXX_STANDARD 20)

set(UNITTEST ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY   ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/binaries)


if(UNITTEST)
    add_subdirectory(googletests/)
    message(" output lib dir " ${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG})
    enable_testing()
endif()

add_subdirectory(libs/generator)
add_subdirectory(libs/controller)
add_subdirectory(libs/context)
add_subdirectory(libs/parser)

add_executable(testproject main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC  database generator)

