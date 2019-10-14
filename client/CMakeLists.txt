cmake_minimum_required(VERSION 3.10)
project(Client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")

include_directories(${SOURCE_DIR})

find_package(Boost REQUIRED)
find_package(SFML COMPONENTS graphics audio network window system REQUIRED)

if (Boost_FOUND AND SFML_FOUND)

    include_directories(${SFML_INCLUDE_DIR})
    include_directories(${Boost_INCLUDE_DIR})

    add_executable(Client ${SOURCE_DIR}/main.cpp ${ALL_SOURCES} ${ALL_HEADERS})
    target_link_libraries(Client ${Boost_LIBRARIES})
    target_link_libraries(Client ${SFML_LIBRARIES})

endif()

