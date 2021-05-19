cmake_minimum_required(VERSION 3.19)
project(Snake)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")

set(SDL2_INCLUDE_DIR c:/libs/SDL/SDL2/include)
set(SDL2_LIB_DIR c:/libs/SDL/SDL2/lib/x86)

set(SDL2_image_INCLUDE_DIR c:/libs/SDL/SDL2_image/include)
set(SDL2_image_LIB_DIR c:/libs/SDL/SDL2_image/lib/x86)

set(SDL2_mixer_INCLUDE_DIR c:/libs/SDL/SDL2_mixer/include)
set(SDL2_mixer_LIB_DIR c:/libs/SDL/SDL2_mixer/lib/x86)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_image_INCLUDE_DIR} ${SDL2_mixer_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR} ${SDL2_image_LIB_DIR} ${SDL2_mixer_LIB_DIR})


add_executable(Snake main.cpp src/Sprite.cpp src/Sprite.h src/utils/Vector2.cpp src/utils/Vector2.h src/Player.cpp src/Player.h src/Apple.cpp src/Apple.h src/utils/Button.cpp src/utils/Button.h src/Menu.cpp src/Menu.h src/Game.cpp src/Game.h)
target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image SDL2_mixer)