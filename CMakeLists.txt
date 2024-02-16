
# CMake configuration

cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

project(Suduko)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(
    SOURCE_FILES
    src/main.cpp
    src/Engine/Engine.cpp
    src/Suduko/Suduko.cpp
)

find_package(SDL2)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS})
