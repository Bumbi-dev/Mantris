#include "Square.h"

Square::Square() : Piece() {
    color = SQUARE_COLOR;
}

Color Square::GetColor() const 
{
    return color;
}

void Square::GetPiece(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE]) const 
{
    ClearPiece(triangles);
    triangles[0][4] = true;
    triangles[0][5] = true;
}
