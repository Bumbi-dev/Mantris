#include "P_Piece.h"

Color P_Piece::GetColor() const 
{
    return P_COLOR;
}

void P_Piece::GetPiece(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE], int pos) const 
{
    ClearPiece(triangles);

    if(pos % 2 == 0)
    {
        triangles[0][4] = true;
        triangles[0][5] = true;
        triangles[0][6] = true;
        triangles[1][5] = true;
        triangles[1][6] = true;
        triangles[1][7] = true;
    }
    else
    {
        triangles[0][2] = true;
        triangles[0][3] = true;
        triangles[0][6] = true;
        triangles[1][3] = true;
        triangles[1][6] = true;
        triangles[1][7] = true;
    }
}
