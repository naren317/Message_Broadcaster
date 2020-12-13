cmake_minimum_required(VERSION 3.17.5)

project(Websocket_Client)

set(SOURCES src/main.cpp
            src/connection_client.cpp)

include_directories(include)

file(GLOB HEADERS include/*.hpp)

find_package(Boost 1.74.0 REQUIRED COMPONENTS system thread)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

if(NOT DEFINED CMAKE_PREFIX_PATH)
    set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_PREFIX_PATH})