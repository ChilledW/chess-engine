//
// Created by Chilled on 30/06/2025.
//

#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <array>
#include <cstdint>
#include <map>
#include <string>

#include "piece.h"
#include "raylib.h"


class ChessBoard {
private:
    std::map<uint8_t, Texture> pieceTextures;
    std::string startingFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"; // Default starting position in FEN
    int cursorPiece;
    int heldPieceIndex;

public:
    bool whitesPov = true; // White's point of view
    int x, y; // Position of the board
    int size;
    int moveHighlightedPrev = -1;
    int moveHighlightedCur = -1;
    int highlightedPiece = -1;
    Color color1, color2; // Colors for the squares
    Color moveHighlightColor1, moveHighlightColor2;
    Color pieceHighlightColor; // Color for highlighting pieces

    std::array<int8_t, 64> squares{piece::none};

    ChessBoard() = default; // Default constructor

    ChessBoard(int x, int y, int size, Color color1, Color color2);

    ~ChessBoard();

    void LoadFEN(const std::string &fen);

    void LoadTextures();

    void Draw() const;

    void HandleUserInput();
};



#endif //CHESSBOARD_H
