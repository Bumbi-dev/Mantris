#include <raylib.h>
#include "Piece.h"

Piece::Piece() {}

Piece::~Piece() {}

void Piece::ClearPiece(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE]) const 
{
    for(int i = 0; i < PIECE_SIZE/2; i++)
        for(int j = 0; j < PIECE_SIZE; j++)
            triangles[i][j] = false;
}