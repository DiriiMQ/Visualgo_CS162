cmake_minimum_required(VERSION 3.24)
project(Visualgo_CS162)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_BUILD_TYPE Release)
find_package(SFML COMPONENTS audio graphics window system REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(Visualgo_CS162 main.cpp include/Window.cpp include/Window.hpp include/libScene/BaseScene.hpp include/MousePosition.cpp include/MousePosition.hpp include/Constants.hpp include/libScene/BaseScene.cpp include/libScene/SLLScene.cpp include/libScene/SLLScene.hpp include/libScene/DLLScene.cpp include/libScene/DLLScene.hpp include/libScene/StaticArrayScene.cpp include/libScene/StaticArrayScene.hpp include/libScene/DynamicArrayScene.cpp include/libScene/DynamicArrayScene.hpp include/libScene/CLLScene.cpp include/libScene/CLLScene.hpp include/libScene/StackScene.cpp include/libScene/StackScene.hpp include/libScene/AllScenes.hpp include/libScene/QueueScene.cpp include/libScene/QueueScene.hpp include/libScene/MainMenu.cpp include/libScene/MainMenu.hpp include/libScene/MenuLinkedList.cpp include/libScene/MenuLinkedList.hpp include/stuff/button.hpp include/stuff/button.cpp include/stuff/button.cpp include/stuff/RoundedRectangleShape.cpp include/stuff/RoundedRectangleShape.hpp include/stuff/Textbox.cpp include/stuff/Textbox.hpp include/stuff/CustomTextbox.cpp include/stuff/CustomTextbox.hpp include/stuff/CustomTextbox.cpp include/stuff/CustomTextbox.cpp include/draw/NodeInfo.cpp include/draw/NodeInfo.hpp include/draw/Arrow.cpp include/draw/Arrow.hpp include/draw/BaseDraw.cpp include/draw/BaseDraw.hpp include/draw/SingleNode.cpp include/draw/SingleNode.hpp include/core/LinkedList.cpp include/core/LinkedList.hpp include/libScene/ControlMenu.cpp include/libScene/ControlMenu.hpp include/stuff/ToStringWithPrecision.hpp include/libScene/Highlighter.hpp include/libScene/Highlighter.cpp include/core/EventAnimation.cpp include/core/EventAnimation.hpp include/core/FileDialog.h include/libScene/MenuDataStructure.cpp include/libScene/MenuDataStructure.hpp include/draw/BackArrow.cpp include/draw/BackArrow.hpp include/core/Vector.h include/draw/Square.cpp include/draw/Square.hpp include/core/Array.cpp include/core/Array.hpp include/draw/SquareInfo.cpp include/draw/SquareInfo.hpp include/core/Random.h include/libScene/MenuArray.cpp include/libScene/MenuArray.hpp)

target_link_libraries(Visualgo_CS162 sfml-graphics sfml-window sfml-system)

if (WIN32)
    target_link_libraries(Visualgo_CS162 ole32 comctl32 oleaut32 uuid)
endif(WIN32)

#add_custom_command(TARGET Visualgo_CS162
#        POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Visualgo_CS162> ..)