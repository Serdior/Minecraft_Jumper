cmake_minimum_required (VERSION 3.10)

project (Minecraft_Jumper)

set (CMAKE_CXX_STANDARD 20)
set (SOURCE_FILES main.cpp Game.cpp Player.cpp Platform.cpp)
set (EXECUTABLE_OUTPUT_PATH ../)

add_executable (Minecraft_Jumper ${SOURCE_FILES})
target_link_libraries (Minecraft_Jumper sfml-audio sfml-graphics sfml-window sfml-system)

