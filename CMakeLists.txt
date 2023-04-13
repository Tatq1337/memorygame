cmake_minimum_required(VERSION 3.23)
project(MemoryGameSDL C)

set(CMAKE_C_STANDARD 17)

set(SDL2_INCLUDE_DIR SDL2/include)
set(SDL2_LIB_DIR SDL2/lib/x86)
include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

set(SDL2_IMG_INCLUDE_DIR SDL2_image/include)
set(SDL2_IMG_LIB_DIR SDL2_image/lib/x86)
include_directories(${SDL2_IMG_INCLUDE_DIR})
link_directories(${SDL2_IMG_LIB_DIR})

set(SDL2_TTF_INCLUDE_DIR SDL2_ttf/include)
set(SDL2_TTF_LIB_DIR SDL2_ttf/lib/x86)
include_directories(${SDL2_TTF_INCLUDE_DIR})
link_directories(${SDL2_TTF_LIB_DIR})

add_executable(MemoryGameSDL main.c)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image SDL2_ttf )
