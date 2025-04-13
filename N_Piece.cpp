#include "N_Piece.h"

//NUKE PIECE
Color N_Piece::GetColor() const 
{
    return N_COLOR;
}

void N_Piece::GetPiece(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE], int pos) const 
{
    ClearPiece(triangles);
    
    if(pos % 4 == 0)
    {
        triangles[0][4] = true;
        triangles[1][2] = true;
        triangles[1][3] = true;
    }
    if(pos % 4 == 1)
    {
        triangles[0][5] = true;
        triangles[0][4] = true;
        triangles[1][3] = true;
    }
    if(pos % 4 == 2)
    {
        triangles[0][2] = true;
        triangles[1][4] = true;
        triangles[1][5] = true;
    }
    if(pos % 4 == 3)
    {
        triangles[0][3] = true;
        triangles[1][4] = true;
        triangles[1][5] = true;
    }
}
