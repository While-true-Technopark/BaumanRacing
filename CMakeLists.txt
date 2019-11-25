cmake_minimum_required(VERSION 3.8)
project(network)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_C_FLAGS "--coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -Wextra -Werror -Wpedantic")
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)

find_package(Boost REQUIRED)
find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(SFML COMPONENTS graphics audio network window system REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

if(Boost_FOUND AND SFML_FOUND)

    include_directories(project/)
    include_directories(${Boost_INCLUDE_DIR})
    include_directories(${SFML_INCLUDE_DIR})

    add_executable(srv.out project/srv.cpp project/network_data.hpp)
    target_link_libraries(srv.out ${Boost_LIBRARIES})
    target_link_libraries(srv.out ${SFML_LIBRARIES})
    target_link_libraries(srv.out nlohmann_json::nlohmann_json)
    
    add_executable(clt.out project/clt.cpp project/network_data.hpp)
    target_link_libraries(clt.out ${Boost_LIBRARIES})
    target_link_libraries(clt.out ${SFML_LIBRARIES})
    target_link_libraries(clt.out nlohmann_json::nlohmann_json)
    
endif()
