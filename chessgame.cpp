#include <iostream>
#include "chessgame.h"
#include "ChessBoard.h"

#include "raylib.h"

namespace chess_game {

    static Color backgroundColor = Color{50, 50, 50, 255};
    ChessBoard board;
    bool canUserMove = true; // Flag to control user moves

    void Init() {

        constexpr int screenWidth = 1600;
        constexpr int screenHeight = screenWidth * 9 / 16;

        int boardSize = screenHeight * 4 / 5;
        int yOffset = (screenHeight - boardSize) / 2;
        int xOffset = yOffset;
        Color color1 = Color{240, 217, 181, 255}; // White
        Color color2 = Color{181, 136, 99, 255}; // Black

        board = ChessBoard(xOffset, yOffset, boardSize, color1, color2);
        board.LoadFEN("STARTING_POSITION"); // Load the default starting position

        InitWindow(screenWidth, screenHeight, "Raylib Example");
        SetTargetFPS(60);

        board.LoadTextures();
    }

    void Run() {

        while(!WindowShouldClose()) {

            board.HandleUserInput();

            BeginDrawing();

            ClearBackground(backgroundColor);

            board.Draw();

            EndDrawing();
        }

        CloseWindow();
    }
}
