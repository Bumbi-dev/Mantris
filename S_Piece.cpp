#include "S_Piece.h"

S_Piece::S_Piece() : Piece() {
    color = RED;
}

Color S_Piece::GetColor() const 
{
    return color;
}

void S_Piece::GetPiece(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE]) const 
{
    ClearPiece(triangles);
    triangles[0][4] = true;
}
