cmake_minimum_required(VERSION 3.8)
project(Server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_C_FLAGS "--coverage")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -Wextra -Werror --pedantic")
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)

include_directories(${SOURCE_DIR}/game_logic)
include_directories(${SOURCE_DIR}/game_manager)

set(LIB_GAME_SERVER
        ${SOURCE_DIR}/game_logic/game_logic.hpp
        ${SOURCE_DIR}/game_logic/game_logic_test.cpp
        ${SOURCE_DIR}/game_manager/game_manager.hpp
        ${SOURCE_DIR}/game_manager/game_manager_test.cpp)
add_library(_game_server STATIC ${LIB_GAME_SERVER})

find_package(Boost REQUIRED)
#find_package(SFML COMPONENTS graphics audio network window system REQUIRED)
find_package(GTest REQUIRED)

if(Boost_FOUND AND GTest_FOUND)

    include_directories(${Boost_INCLUDE_DIR})
    #include_directories(${SFML_INCLUDE_DIR})
    include_directories(${GTEST_INCLUDE_DIRS})

# link game_manager
    add_executable(game_manager_test.out ${SOURCE_DIR}/game_manager/game_manager_test.cpp)
    target_link_libraries(game_manager_test.out _game_server)
    target_link_libraries(game_manager_test.out ${GTEST_LIBRARIES})
    target_link_libraries(game_manager_test.out pthread)
    target_link_libraries(game_manager_test.out gmock)
    target_link_libraries(game_manager_test.out ${Boost_LIBRARIES})
    #target_link_libraries(game_manager_test.out ${SFML_LIBRARIES})

# link game_logic
    add_executable(game_logic_test.out ${SOURCE_DIR}/game_logic/game_logic_test.cpp)
    target_link_libraries(game_logic_test.out _game_server)
    target_link_libraries(game_logic_test.out ${GTEST_LIBRARIES})
    target_link_libraries(game_logic_test.out pthread)
    target_link_libraries(game_logic_test.out gmock)
    target_link_libraries(game_logic_test.out ${Boost_LIBRARIES})
    #target_link_libraries(game_logic_test.out ${SFML_LIBRARIES})
    
endif()