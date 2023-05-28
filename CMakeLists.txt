cmake_minimum_required(VERSION 3.24)
project(tetris_mirea)

set(CMAKE_CXX_STANDARD 17)

add_executable(tetris_mirea WIN32 main.cpp tetris.cpp board.cpp)
file(COPY fonts DESTINATION ${CMAKE_BINARY_DIR})
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "E:/Work/C++/tetris-mirea/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)
file(COPY "img" DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(tetris_mirea sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
set(CMAKE_EXE_LINKER_FLAGS -static)
