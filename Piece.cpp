#include <raylib.h>
#include "Piece.h"
#include "Utils.h"

Piece::Piece() {}

Piece::~Piece() {}

void Piece::ClearPiece(Color (&triangles)[8][8]) const {
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            triangles[i][j] = GRID_TRIANGLE;
}