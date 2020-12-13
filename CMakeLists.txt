cmake_minimum_required(VERSION 3.17.5)

project(Message_Broadcaster)

set(CMAKE_BUILD_TYPE release)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-g) # Helps in gdb debug

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Message_Broadcasting_Server)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Websocket_Client)
