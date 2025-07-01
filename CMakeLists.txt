cmake_minimum_required(VERSION 3.29)
project(chessengine)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(ext/raylib)

add_executable(chessengine main.cpp
        chessgame.cpp
        chessgame.h
        ChessBoard.cpp
        ChessBoard.h
        Piece.cpp
        Piece.h
)

target_link_libraries(chessengine raylib)
