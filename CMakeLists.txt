cmake_minimum_required(VERSION 3.0.0)
project(GameOfLife_Cpp VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

find_package(SDL2 REQUIRED)

# add_subdirectory(${PROJECT_SOURCE_DIR}/external)

add_library(gol_lib
    STATIC
        ${PROJECT_SOURCE_DIR}/src/SDL_FontCache.c
        ${PROJECT_SOURCE_DIR}/src/sdl_funcs.cpp
        ${PROJECT_SOURCE_DIR}/src/datastruct.cpp
        ${PROJECT_SOURCE_DIR}/src/ds_cellmap.cpp
)

target_include_directories(gol_lib
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(gol_binary
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)

target_link_libraries(gol_binary
    PRIVATE
        gol_lib
        SDL2
        SDL2_ttf
)
