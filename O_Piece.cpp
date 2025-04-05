#include "O_Piece.h"

O_Piece::O_Piece() : Piece() {
    color = SQUARE_COLOR;
}

Color O_Piece::GetColor() const 
{
    return color;
}

void O_Piece::GetPiece(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE]) const 
{
    ClearPiece(triangles);
    triangles[0][4] = true;
    triangles[0][5] = true;
}
