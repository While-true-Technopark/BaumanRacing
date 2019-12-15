cmake_minimum_required(VERSION 3.8)
project(Server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_C_FLAGS "--coverage")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -Wextra -Werror -Wpedantic")
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)

set(TINYXML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/tinyxml2")
set(TRANSFER_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../transfer_lib")

set(ALL_SOURCES

        ${TINYXML_DIR}/tinyxml2.cpp  # TODO: подключать как отдельную либу
        ${TRANSFER_LIB_DIR}/transfer/message.cpp
        ${TRANSFER_LIB_DIR}/transfer/command.cpp
        
        ${SOURCE_DIR}/user/user.cpp
        
        ${SOURCE_DIR}/game_manager/map.cpp
        ${SOURCE_DIR}/game_manager/game_manager.cpp
        
        ${SOURCE_DIR}/users_room/users_room.cpp
        
        ${SOURCE_DIR}/server/server.cpp
)

set(ALL_HEADERS 
    ${TINYXML_DIR}/ # TODO: подключать как отдельную либу
    ${TRANSFER_LIB_DIR}/config/
    ${TRANSFER_LIB_DIR}/transfer/
    
    ${SOURCE_DIR}/user/
    ${SOURCE_DIR}/game_manager/
    ${SOURCE_DIR}/users_room/
    ${SOURCE_DIR}/server/
)

find_package(SFML COMPONENTS graphics audio network window system REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
include_directories(${ALL_HEADERS})

add_executable(server.out ${ALL_SOURCES} ${SOURCE_DIR}/start_server.cpp)
target_link_libraries(server.out pthread)
target_link_libraries(server.out ${SFML_LIBRARIES})
target_link_libraries(server.out nlohmann_json::nlohmann_json)
