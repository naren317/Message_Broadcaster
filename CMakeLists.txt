CMAKE_MINIMUM_REQUIRED(VERSION 3.17.5) # Tested on cmake 3.17.5 as of now

project(Message_Broadcasting_Server)

set(CMAKE_CXX_STANDARD 17)
option(INCLUDE_BEAST OFF)

if(INCLUDE_BEAST)
    add_definitions(-DINCLUDE_BEAST_)
endif(INCLUDE_BEAST)

include_directories(${CMAKE_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS})
file(GLOB HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)
set(SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/connection_server.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/routine_handler.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/src/broadcast_module.cpp)

find_package(Boost 1.74.0 REQUIRED COMPONENTS system thread)
add_executable(${PROJECT_NAME}  ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} -lrt)