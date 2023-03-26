cmake_minimum_required(VERSION 3.24)
project(Visualgo_CS162)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
find_package(SFML COMPONENTS audio graphics window system REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(Visualgo_CS162 main.cpp include/Window.cpp include/Window.hpp include/BaseScene.hpp include/MousePosition.cpp include/MousePosition.hpp include/Constants.hpp include/BaseScene.cpp include/Stuff.cpp include/Stuff.hpp include/RoundedRectangleShape.cpp include/RoundedRectangleShape.hpp)

target_link_libraries(Visualgo_CS162 sfml-graphics sfml-window sfml-system)