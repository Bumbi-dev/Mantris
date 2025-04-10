#include "T_Piece.h"

//T PIECE
Color T_Piece::GetColor() const 
{
    return T_COLOR;
}

void T_Piece::GetPiece(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE], int pos) const 
{
    ClearPiece(triangles);
    if(pos == 0)
    {
        triangles[0][4] = true;
        triangles[0][5] = true;
        triangles[1][2] = true;
        triangles[1][3] = true;
        triangles[1][4] = true;
        triangles[1][5] = true;
        triangles[1][6] = true;  
        triangles[1][7] = true;
    }
    if(pos == 1)
    {
        triangles[0][4] = true;
        triangles[0][5] = true;
        triangles[1][4] = true;
        triangles[1][5] = true;
        triangles[1][6] = true;  
        triangles[1][7] = true;
        triangles[2][4] = true;
        triangles[2][5] = true;
    }
    if(pos == 2)
    {
        triangles[1][2] = true;
        triangles[1][3] = true;
        triangles[1][4] = true;
        triangles[1][5] = true;
        triangles[1][6] = true;  
        triangles[1][7] = true;
        triangles[2][4] = true;
        triangles[2][5] = true;
    }
    if(pos == 3)
    {
        triangles[0][4] = true;
        triangles[0][5] = true;
        triangles[1][2] = true;
        triangles[1][3] = true;
        triangles[1][4] = true;
        triangles[1][5] = true;
        triangles[2][4] = true;
        triangles[2][5] = true;
    }
}