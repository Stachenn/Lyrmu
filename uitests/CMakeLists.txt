cmake_minimum_required(VERSION 3.5)

project(lyrmu VERSION 0.1)

find_package(SDL2 REQUIRED)

set(SOURCES
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(lyrmu SDL2 SDL2_image SDL2_ttf)

include_directories(SDL2Test ${SDL2_INCLUDE_DIRS})
