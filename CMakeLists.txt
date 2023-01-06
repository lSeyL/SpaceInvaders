cmake_minimum_required(VERSION 3.24)
project(SpaceInvaders)

set(CMAKE_CXX_STANDARD 14)

add_executable(SpaceInvaders main.cpp Classes/Player.cpp Classes/Player.h Classes/Alien.cpp Classes/Alien.h Classes/Bullet.cpp Classes/Bullet.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
target_link_libraries(SpaceInvaders sfml-system sfml-window sfml-graphics sfml-audio sfml-network)