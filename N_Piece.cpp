#include "N_Piece.h"

Color N_Piece::GetColor() const 
{
    return N_COLOR;
}

void N_Piece::GetPiece(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE], int pos) const 
{
    ClearPiece(triangles);
    if(pos % 2 == 0)
    {
        triangles[0][4] = true;
        triangles[1][2] = true;
        triangles[1][3] = true;
    }
    else 
    {
        triangles[0][5] = true;
        triangles[0][4] = true;
        triangles[1][3] = true;
    }
}
