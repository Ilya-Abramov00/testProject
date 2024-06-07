cmake_minimum_required(VERSION 3.5)

project(testproject)

set(CMAKE_CXX_STANDARD 17)

set(UNITTEST ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY   ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/binaries)



if(UNITTEST)
    add_subdirectory(googletests/)
endif()


add_subdirectory(libs/generator)



if(UNITTEST)
    message(" output lib dir " ${CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG})
    enable_testing()

endif()

add_executable(testproject main.cpp)


