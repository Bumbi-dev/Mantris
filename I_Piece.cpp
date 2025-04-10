#include "I_Piece.h"

//LINE PIECE
Color I_Piece::GetColor() const 
{
    return I_COLOR;
}

void I_Piece::GetPiece(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE], int pos) const 
{
    ClearPiece(triangles);
    if(pos % 2 == 0)
    {
        triangles[0][4] = true;
        triangles[0][5] = true;
        triangles[1][4] = true;
        triangles[1][5] = true;
        triangles[2][4] = true;
        triangles[2][5] = true;
    }
    else 
    {
        triangles[1][2] = true;
        triangles[1][3] = true;
        triangles[1][4] = true;
        triangles[1][5] = true;
        triangles[1][6] = true;
        triangles[1][7] = true;
    }
}
