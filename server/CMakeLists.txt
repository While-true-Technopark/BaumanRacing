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

include_directories(${SOURCE_DIR}/transfer_lib/config) # TODO: подключать как отдельную либу
include_directories(${SOURCE_DIR}/transfer_lib/transfer)
include_directories(${SOURCE_DIR}/user)
include_directories(${TINYXML_DIR})  # TODO: подключать как отдельную либу
include_directories(${SOURCE_DIR}/game_manager)
include_directories(${SOURCE_DIR}/users_room)
include_directories(${SOURCE_DIR}/server)
#include_directories(${SOURCE_DIR}/game_logic)

set(LIB_GAME_SERVER

        ${SOURCE_DIR}/transfer_lib/transfer/command.cpp  # TODO: подключать как отдельную либу
        ${SOURCE_DIR}/transfer_lib/transfer/message.cpp
        
        ${SOURCE_DIR}/user/user.cpp
        
        ${TINYXML_DIR}/tinyxml2.cpp  # TODO: подключать как отдельную либу
        ${SOURCE_DIR}/game_manager/map.cpp
        ${SOURCE_DIR}/game_manager/game_manager.cpp
        
        ${SOURCE_DIR}/users_room/users_room.cpp
        
        ${SOURCE_DIR}/server/server.cpp
)

add_library(_game_server STATIC ${LIB_GAME_SERVER})

find_package(SFML COMPONENTS graphics audio network window system REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

add_executable(srv.out ${SOURCE_DIR}/start_server.cpp)
target_link_libraries(srv.out _game_server)
target_link_libraries(srv.out ${SFML_LIBRARIES})
target_link_libraries(srv.out nlohmann_json::nlohmann_json)

add_executable(clt.out ${SOURCE_DIR}/test_client.cpp)
target_link_libraries(clt.out _game_server)
target_link_libraries(clt.out ${SFML_LIBRARIES})
target_link_libraries(clt.out nlohmann_json::nlohmann_json)

#find_package(Boost REQUIRED)
#find_package(GTest REQUIRED)

#if(Boost_FOUND AND GTest_FOUND)

    #include_directories(${Boost_INCLUDE_DIR})
    #include_directories(${GTEST_INCLUDE_DIRS})

# link game_manager
    #add_executable(game_manager_test.out ${SOURCE_DIR}/game_manager/game_manager_test.cpp)
    #target_link_libraries(game_manager_test.out _game_server)
    #target_link_libraries(game_manager_test.out ${GTEST_LIBRARIES})
    #target_link_libraries(game_manager_test.out pthread)
    #target_link_libraries(game_manager_test.out gmock)
    #target_link_libraries(game_manager_test.out ${Boost_LIBRARIES})
    #target_link_libraries(game_manager_test.out ${SFML_LIBRARIES})

# link game_logic
    #add_executable(game_logic_test.out ${SOURCE_DIR}/game_logic/game_logic_test.cpp)
    #target_link_libraries(game_logic_test.out _game_server)
    #target_link_libraries(game_logic_test.out ${GTEST_LIBRARIES})
    #target_link_libraries(game_logic_test.out pthread)
    #target_link_libraries(game_logic_test.out gmock)
    #target_link_libraries(game_logic_test.out ${Boost_LIBRARIES})
    #target_link_libraries(game_logic_test.out ${SFML_LIBRARIES})
    
#endif()
