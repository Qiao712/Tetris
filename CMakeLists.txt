cmake_minimum_required(VERSION 3.16)

# Project name: Tetris
project(tetris)

file (GLOB SOURCES "src/*.cpp")

add_executable(tetris_test ${SOURCES})

target_include_directories(tetris_test
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(tetris_test
    PRIVATE
        SDL2
        SDL2main
)