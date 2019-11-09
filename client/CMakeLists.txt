cmake_minimum_required(VERSION 3.10)
project(Client)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")

include_directories(${SOURCE_DIR})

set(ALL_SOURCES ${SOURCE_DIR}/Application/application.cpp
                ${SOURCE_DIR}/Base_builder/base_builder.cpp
                ${SOURCE_DIR}/Base_module/base_module.cpp
		${SOURCE_DIR}/Event/event.cpp
		${SOURCE_DIR}/Event_manager/event_manager.cpp
		${SOURCE_DIR}/Game_builder/game_builder.cpp
                ${SOURCE_DIR}/Game_context/game_context.cpp
		${SOURCE_DIR}/Input/input.cpp
		${SOURCE_DIR}/Loader/loader.cpp
		${SOURCE_DIR}/Map_builder/map_builder.cpp
                ${SOURCE_DIR}/Menu_builder/menu_builder.cpp
		${SOURCE_DIR}/Network/network.cpp
		${SOURCE_DIR}/Renderer/renderer.cpp
                )

set(ALL_HEADERS ${SOURCE_DIR}/Application/
                ${SOURCE_DIR}/Base_builder/
                ${SOURCE_DIR}/Base_module/
		${SOURCE_DIR}/Event/
		${SOURCE_DIR}/Event_manager/
		${SOURCE_DIR}/Game_builder/
                ${SOURCE_DIR}/Game_context/
		${SOURCE_DIR}/Input/
		${SOURCE_DIR}/Loader/
		${SOURCE_DIR}/Map_builder/
                ${SOURCE_DIR}/Menu_builder/
		${SOURCE_DIR}/Network/
		${SOURCE_DIR}/Renderer/
		${SOURCE_DIR}/Event_throwable/
                )


find_package(Boost REQUIRED)
find_package(SFML COMPONENTS graphics audio network window system REQUIRED)

if (Boost_FOUND AND SFML_FOUND)

    include_directories(${SFML_INCLUDE_DIR})
    include_directories(${Boost_INCLUDE_DIR})
    include_directories(${ALL_HEADERS})

    add_executable(Client.out ${SOURCE_DIR}/main.cpp ${ALL_SOURCES})
    target_link_libraries(Client.out ${Boost_LIBRARIES})
    target_link_libraries(Client.out ${SFML_LIBRARIES})


    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
    add_executable(Client_tests.out ${SOURCE_DIR}/Application/application_tests.cpp)
    target_link_libraries(Client_tests.out ${GTEST_LIBRARIES})
    target_link_libraries(Client_tests.out pthread)
    target_link_libraries(Client_tests.out gmock)
    target_link_libraries(Client_tests.out ${Boost_LIBRARIES})
    target_link_libraries(Client_tests.out ${SFML_LIBRARIES})

else()
    if (Boost_FOUND)
        message("Boost library was not founded. Look there: https://github.com/boostorg/boost")
    endif()
    if (SFML_FOUND)
        message("SFML library was not founded. Look there: https://github.com/SFML/SFML")
    endif()
endif()

