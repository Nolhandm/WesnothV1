cmake_minimum_required(VERSION 3.24)
project(Wesnoth_AI_Cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Wesnoth_AI_Cpp
        Player.cpp
        Player.hpp
        Unit.cpp
        Unit.hpp main.cpp Map.hpp Map.cpp Utilitaire.cpp Utilitaire.hpp Utilitaire.cpp Utilitaire.cpp Utilitaire.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include)
target_link_libraries(Wesnoth_AI_Cpp sfml-system sfml-window sfml-graphics sfml-audio)
