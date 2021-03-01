cmake_minimum_required(VERSION 3.15)
project(my_Frogger)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Entity/Map.cpp Entity/Car.cpp Abstract/Character.cpp Entity/Frog.cpp Entity/Log.cpp Entity/Map.cpp Entity/GameWorld.cpp Entity/Scene.cpp Interface/IObservable.hh Interface/IObserver.hh Interface/ISerializable.hh Assets/Json/json.hpp Abstract/AbstractEntity.cpp  Factory/EntityFactory.cpp TimeManager/TimeManager.cpp SFML/TileMap.cpp SFML/Animation.cpp SFML/TextureRessources.cpp SFML/Menu.cpp Entity/Snake.cpp Entity/Snake.hh Entity/Fly.cpp Entity/Fly.hh)



include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(my_Frogger ${SOURCE_FILES} Entity/Fly.cpp Entity/Fly.hh)
target_link_libraries(my_Frogger ${CONAN_LIBS})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(my_Frogger ${SFML_LIBRARIES})
endif()


if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()

