//
// Created by Chilled on 01/07/2025.
//

#ifndef PIECE_H
#define PIECE_H

#include <cstdint>

namespace piece {
    constexpr uint8_t none = 0;
    constexpr uint8_t pawn = 1;
    constexpr uint8_t knight = 2;
    constexpr uint8_t bishop = 3;
    constexpr uint8_t rook = 4;
    constexpr uint8_t queen = 5;
    constexpr uint8_t king = 6;

    constexpr uint8_t white = 8;
    constexpr uint8_t black = 16;

    uint8_t static color(uint8_t piece);
    uint8_t static isColor(uint8_t piece, uint8_t color);
    uint8_t static type(uint8_t piece);
    bool static isSliding(uint8_t piece);
}

#endif //PIECE_H
