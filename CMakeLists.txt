cmake_minimum_required(VERSION 3.24)
project (Visualgo_CS162)

set(CMAKE_CXX_STANDARD 17)
set(FLTK_DIR ~/fltk)

find_package(FLTK REQUIRED NO_MODULE)

add_executable(Visualgo_CS162 WIN32 MACOSX_BUNDLE main.cpp include/MyConstants.cpp include/MyConstants.h include/MainWindow.cpp include/MainWindow.h)
if (APPLE)
    target_link_libraries(Visualgo_CS162 "-framework cocoa")
endif (APPLE)

target_include_directories(Visualgo_CS162 PUBLIC ${FLTK_INCLUDE_DIRS})

target_link_libraries(Visualgo_CS162 fltk)