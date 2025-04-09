#include "V_Piece.h"

Color V_Piece::GetColor() const 
{
    return V_COLOR;
}

void V_Piece::GetPiece(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE], int pos) const 
{
    ClearPiece(triangles);

    if(pos % 2 == 0)
        triangles[0][4] = true;
    else 
        triangles[0][5] = true;
     
}
