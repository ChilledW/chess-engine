//
// Created by Chilled on 01/07/2025.
//

#include "piece.h"

#include <cstdint>

namespace piece {
    uint8_t static color(uint8_t piece) {
        return piece & (white | black);
    }

    uint8_t static isColor(uint8_t piece, uint8_t color) {
        return (piece & (white | black)) == color;
    }

    uint8_t static type(uint8_t piece) {
        return piece & (pawn | knight | bishop | rook | queen | king);
    }

    bool static isSliding(uint8_t piece) {
        return (piece & (rook | bishop | queen)) != 0;
    }

}
