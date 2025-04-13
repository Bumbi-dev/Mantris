#include <raylib.h>
#include "Piece.h"

int cells = 0;

void Piece::ClearPiece(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE]) const 
{
    for(int i = 0; i < PIECE_SIZE/2; i++)
        for(int j = 0; j < PIECE_SIZE; j++)
            triangles[i][j] = false;
}

int Piece::GetCells(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE]) const 
{
    if(cells == 0)
        for(int i = 0; i < PIECE_SIZE/2; i++)
            for(int j = 0; j < PIECE_SIZE; j++)
                if(triangles[i][j])
                    cells++;
    return cells;
}