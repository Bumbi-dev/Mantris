#include "Square_Piece.h"

Square_Piece::Square_Piece() : Piece() {
    color = SQUARE_COLOR;
}

Color Square_Piece::GetColor() const 
{
    return color;
}

void Square_Piece::GetPiece(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE]) const 
{
    ClearPiece(triangles);
    triangles[0][4] = true;
    triangles[0][5] = true;
}
