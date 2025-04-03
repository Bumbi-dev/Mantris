#include "T_Piece.h"

T_Piece::T_Piece() : Piece() {
    color = T_COLOR;
}

Color T_Piece::GetColor() const 
{
    return color;
}

void T_Piece::GetPiece(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE]) const 
{
    ClearPiece(triangles);
    triangles[0][3] = true;
}
