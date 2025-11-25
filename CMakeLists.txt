cmake_minimum_required(VERSION 3.5)

project(Velo_Bilheran LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(OpenGL main.cpp 
                object.cpp
    object.h
    renderer.cpp
    renderer.h
    shader.cpp
    shader.h
    texture.cpp
    texture.h
    uvbuffer.cpp
    uvbuffer.h
    vertexarray.cpp
    vertexarray.h
    vertexbuffer.cpp
    vertexbuffer.h
    window.h
    window.cpp
    walls.h 
    walls.cpp
    piece.h
    piece.cpp
    pieceManager.h
    pieceManager.cpp
    tetrisGame.h
    tetrisGame.cpp
    
    stb_image/stb_image.cpp
    stb_image/stb_image.h)

target_link_libraries(OpenGL glfw GLEW libGLEW.so libGLU.so libGL.so)
