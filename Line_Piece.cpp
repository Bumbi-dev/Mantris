#include "Line_Piece.h"

Line_Piece::Line_Piece() : Piece() {
    color = LINE_COLOR;
}

Color Line_Piece::GetColor() const 
{
    return color;
}

void Line_Piece::GetPiece(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE]) const 
{
    ClearPiece(triangles);
    triangles[0][4] = true;
    triangles[0][5] = true;
    triangles[1][4] = true;
    triangles[1][5] = true;
    triangles[2][4] = true;
    triangles[2][5] = true;
}
