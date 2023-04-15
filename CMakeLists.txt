cmake_minimum_required(VERSION 3.24)
project(Visualgo_CS162)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
find_package(SFML COMPONENTS audio graphics window system REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(Visualgo_CS162 main.cpp include/Window.cpp include/Window.hpp include/libScene/BaseScene.hpp include/MousePosition.cpp include/MousePosition.hpp include/Constants.hpp include/libScene/BaseScene.cpp include/libScene/SLLScene.cpp include/libScene/SLLScene.hpp include/libScene/DLLScene.cpp include/libScene/DLLScene.hpp include/libScene/StaticArrayScene.cpp include/libScene/StaticArrayScene.hpp include/libScene/DynamicArrayScene.cpp include/libScene/DynamicArrayScene.hpp include/libScene/CLLScene.cpp include/libScene/CLLScene.hpp include/libScene/StackScene.cpp include/libScene/StackScene.hpp include/libScene/AllScenes.hpp include/libScene/QueueScene.cpp include/libScene/QueueScene.hpp include/libScene/MainMenu.cpp include/libScene/MainMenu.hpp include/libScene/MenuLinkedList.cpp include/libScene/MenuLinkedList.hpp include/stuff/button.hpp include/stuff/button.cpp include/stuff/button.cpp include/stuff/RoundedRectangleShape.cpp include/stuff/RoundedRectangleShape.hpp include/stuff/Textbox.cpp include/stuff/Textbox.hpp include/stuff/CustomTextbox.cpp include/stuff/CustomTextbox.hpp include/stuff/CustomTextbox.cpp include/stuff/CustomTextbox.cpp include/draw/NodeInfo.cpp include/draw/NodeInfo.hpp include/draw/Arrow.cpp include/draw/Arrow.hpp include/draw/BaseDraw.cpp include/draw/BaseDraw.hpp include/draw/SingleNode.cpp include/draw/SingleNode.hpp include/core/LinkedList.cpp include/core/LinkedList.hpp include/libScene/ControlMenu.cpp include/libScene/ControlMenu.hpp include/stuff/ToStringWithPrecision.hpp include/libScene/HIghlighter.cpp include/libScene/HIghlighter.hpp include/libScene/HIghlighter.cpp)

target_link_libraries(Visualgo_CS162 sfml-graphics sfml-window sfml-system)

#add_custom_command(TARGET Visualgo_CS162
#        POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Visualgo_CS162> ..)