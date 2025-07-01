#include "ChessBoard.h"
#include "piece.h"

#include <string>
#include <iostream>

#include "raylib.h"

ChessBoard::ChessBoard(int x, int y, int size, Color color1, Color color2)
    : x(x), y(y), size(size), moveHighlightedPrev(), moveHighlightedCur(), color1(color1), color2(color2),
        heldPieceIndex(),
        moveHighlightColor1(Color{150, 170, 10, 90}),
        moveHighlightColor2(150, 170, 10, 150),
        pieceHighlightColor(Color{140, 190, 0, 150}),
        cursorPiece(piece::none) {
}

ChessBoard::~ChessBoard() {
    // if textures are loaded, unload them
    for (auto& [piece, texture] : pieceTextures) {
        if (texture.id != 0) { // Check if the texture is loaded
            UnloadTexture(texture);
        }
    }
}


void ChessBoard::LoadFEN(const std::string& inputFen) {
    squares = {piece::none};
    std::string fen;
    if (inputFen == "STARTING_POSITION") fen = startingFEN; // Use the default starting position if "STARTING_POSITION" is passed
    else fen = inputFen; // Otherwise, use the provided FEN string

    int row = 8;
    int col = 0;

    for (char c : fen) {
        if (c == ' ') break; // Stop at the first space, which indicates the end of the piece placement

        if (c >= '1' && c <= '8') {
            // If it's a number, skip that many squares
            col += c - '0';
        } else if (c == '/') {
            // Move to the next row
            row--;
            col = 0;
        } else {
            // Place the piece on the board
            uint8_t piece = 0;
            switch (c) {
                case 'P': piece = piece::pawn | piece::white; break;
                case 'p': piece = piece::pawn | piece::black; break;
                case 'R': piece = piece::rook | piece::white; break;
                case 'r': piece = piece::rook | piece::black; break;
                case 'N': piece = piece::knight | piece::white; break;
                case 'n': piece = piece::knight | piece::black; break;
                case 'B': piece = piece::bishop | piece::white; break;
                case 'b': piece = piece::bishop | piece::black; break;
                case 'Q': piece = piece::queen | piece::white; break;
                case 'q': piece = piece::queen | piece::black; break;
                case 'K': piece = piece::king | piece::white; break;
                case 'k': piece = piece::king | piece::black; break;
                default: continue; // Ignore any other characters
            }
            squares[(row - 1) * 8 + col] = piece;
            col++;
        }
    }
}

void ChessBoard::LoadTextures() {
    // The squares go from A1 to H8, which is 64 squares in total. A1 is at index 0 and H8 is at index 63.
    // index 1 is A2, index 2 is A3, and so on.
    Image whitePawnI = LoadImage("resources/pieces/white-pawn.png");
    pieceTextures[piece::pawn | piece::white] = LoadTextureFromImage(whitePawnI);
    Image blackPawnI = LoadImage("resources/pieces/black-pawn.png");
    pieceTextures[piece::pawn | piece::black] = LoadTextureFromImage(blackPawnI);
    Image whiteRookI = LoadImage("resources/pieces/white-rook.png");
    pieceTextures[piece::rook | piece::white] = LoadTextureFromImage(whiteRookI);
    Image blackRookI = LoadImage("resources/pieces/black-rook.png");
    pieceTextures[piece::rook | piece::black] = LoadTextureFromImage(blackRookI);
    Image whiteKnightI = LoadImage("resources/pieces/white-knight.png");
    pieceTextures[piece::knight | piece::white] = LoadTextureFromImage(whiteKnightI);
    Image blackKnightI = LoadImage("resources/pieces/black-knight.png");
    pieceTextures[piece::knight | piece::black] = LoadTextureFromImage(blackKnightI);
    Image whiteBishopI = LoadImage("resources/pieces/white-bishop.png");
    pieceTextures[piece::bishop | piece::white] = LoadTextureFromImage(whiteBishopI);
    Image blackBishopI = LoadImage("resources/pieces/black-bishop.png");
    pieceTextures[piece::bishop | piece::black] = LoadTextureFromImage(blackBishopI);
    Image whiteQueenI = LoadImage("resources/pieces/white-queen.png");
    pieceTextures[piece::queen | piece::white] = LoadTextureFromImage(whiteQueenI);
    Image blackQueenI = LoadImage("resources/pieces/black-queen.png");
    pieceTextures[piece::queen | piece::black] = LoadTextureFromImage(blackQueenI);
    Image whiteKingI = LoadImage("resources/pieces/white-king.png");
    pieceTextures[piece::king | piece::white] = LoadTextureFromImage(whiteKingI);
    Image blackKingI = LoadImage("resources/pieces/black-king.png");
    pieceTextures[piece::king | piece::black] = LoadTextureFromImage(blackKingI);
    UnloadImage(whitePawnI);
    UnloadImage(blackPawnI);
    UnloadImage(whiteRookI);
    UnloadImage(blackRookI);
    UnloadImage(whiteKnightI);
    UnloadImage(blackKnightI);
    UnloadImage(whiteBishopI);
    UnloadImage(blackBishopI);
    UnloadImage(whiteQueenI);
    UnloadImage(blackQueenI);
    UnloadImage(whiteKingI);
    UnloadImage(blackKingI);

    for (auto& [piece, texture] : pieceTextures) {
        SetTextureFilter(texture, TEXTURE_FILTER_BILINEAR);
    }

}

void ChessBoard::Draw() const {
    // Draw the chessboard squares
    const int squareSize = size / 8;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Color squareColor = ((row + col + (1*!whitesPov)) % 2 == 0) ? color1 : color2;
            DrawRectangle(x + col * squareSize, y + row * squareSize, squareSize, squareSize, squareColor);
        }
    }
    if (moveHighlightedPrev != moveHighlightedCur) {
        int prevRow = whitesPov ? (7 - moveHighlightedPrev / 8) : (moveHighlightedPrev / 8);
        int prevCol = whitesPov ? (moveHighlightedPrev % 8) : (7 - moveHighlightedPrev % 8);
        int curRow = whitesPov ? (7 - moveHighlightedCur / 8) : (moveHighlightedCur / 8);
        int curCol = whitesPov ? (moveHighlightedCur % 8) : (7 - moveHighlightedCur % 8);

        DrawRectangle(x + prevCol * squareSize, y + prevRow * squareSize, squareSize, squareSize, moveHighlightColor1);
        DrawRectangle(x + curCol * squareSize, y + curRow * squareSize, squareSize, squareSize, moveHighlightColor2);
    }

    // Draw the chess pieces
    int pieceSize = squareSize * 1.f;
    // Starting position for the first piece
    int currentXPos = 0;
    int currentYPos = size - pieceSize;
    int yOffset = (squareSize - pieceSize) / 2; // Center the piece vertically in the square
    int xOffset = (squareSize - pieceSize) / 2; // Center the piece horizontally in the square

    Texture2D pieceTexture;
    for (int i = 0; i < 64; i++) {
        if (squares[i] == piece::none) {
            continue; // Skip empty squares
        }
        pieceTexture = pieceTextures.at(squares[i]);
        if (whitesPov) {
            // start drawing from the bottom
            currentYPos = size - (i / 8 + 1) * squareSize;
            currentXPos = (i % 8) * squareSize;

        } else {
            currentYPos = (i / 8) * squareSize;
            currentXPos = (7 - (i % 8)) * squareSize;
        }
        Rectangle pieceRect = { static_cast<float>(x + currentXPos+xOffset), static_cast<float>(y + currentYPos+yOffset), static_cast<float>(pieceSize), static_cast<float>(pieceSize) };
        Rectangle sourceRect = { 0, 0, static_cast<float>(pieceTexture.width), static_cast<float>(pieceTexture.height) };
        DrawTexturePro(pieceTexture, sourceRect, pieceRect, Vector2{0, 0}, 0.0f, WHITE);

        // Draw the piece at the cursor
    if (cursorPiece != piece::none) {
        pieceTexture = pieceTextures.at(cursorPiece);
        // Draw the cursor piece at the mouse position
        Vector2 mousePos = GetMousePosition();
        Rectangle cursorRect = { mousePos.x - pieceSize/2, mousePos.y - pieceSize/2, static_cast<float>(pieceSize), static_cast<float>(pieceSize) };
        DrawTexturePro(pieceTexture, sourceRect, cursorRect, Vector2{0, 0}, 0.0f, WHITE);
    }
         

    }
}

void ChessBoard::HandleUserInput() {
    if (IsKeyPressed(KEY_SPACE)) whitesPov = !whitesPov;
    if (IsKeyPressed(KEY_R)) LoadFEN("STARTING_POSITION");
    // check if the mouse is within the bounds of the chessboard
    Vector2 mousePos = GetMousePosition();
    if (mousePos.x < x || mousePos.x > x + size || mousePos.y < y || mousePos.y > y + size) {
        return; // Mouse is outside the chessboard bounds
    }
    int col = (mousePos.x - x) / (size / 8);
    int row = (mousePos.y - y) / (size / 8);
    int index = whitesPov ? (7 - row) * 8 + col : row * 8 + (7 - col);
    std::cout << "held index: " << heldPieceIndex << std::endl;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (cursorPiece == piece::none) {
            cursorPiece = squares[index];
            heldPieceIndex = index; // Store the index of the piece being held
            squares[index] = piece::none; // Remove the piece from the board
        }
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && cursorPiece != piece::none) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            std::cout << "Right click detected, placing piece at index: " << index << std::endl;
            squares[heldPieceIndex] = cursorPiece;
            cursorPiece = piece::none;
            highlightedPiece = -1; // Deselect the highlighted piece
        }
    } else if (cursorPiece != piece::none) {
        squares[index] = cursorPiece;
        cursorPiece = piece::none;
        if (heldPieceIndex != index) {
            moveHighlightedPrev = heldPieceIndex;
            moveHighlightedCur = index; // Update the highlighted move
        }
    }
}