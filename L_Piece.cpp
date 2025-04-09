#include "L_Piece.h"

Color L_Piece::GetColor() const 
{
    return L_COLOR;
}

void L_Piece::GetPiece(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE], int pos) const 
{
    ClearPiece(triangles);

    if(pos % 2 == 0) {
        triangles[0][6] = true;
        triangles[0][7] = true;
        triangles[1][2] = true;
        triangles[1][3] = true;
        triangles[1][4] = true;
        triangles[1][5] = true;
        triangles[1][6] = true;
        triangles[1][7] = true;
    }
    else 
    {
        triangles[0][8] = true;
        triangles[0][9] = true;
        triangles[1][0] = true;
        triangles[1][1] = true;
        triangles[1][2] = true;
        triangles[1][7] = true;
        triangles[1][8] = true;
        triangles[1][9] = true;
    }
}