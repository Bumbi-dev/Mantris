#pragma once

#include "Utils.h"

class Piece 
{
public:
    virtual void GetPiece(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE], int pos) const = 0;
    virtual Color GetColor() const = 0;

    void ClearPiece(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE]) const;

    int GetCells(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE]) const;
};
