#pragma once
#include <raylib.h> 
#include "Utils.h"
class Piece 
{
public:
    Piece(); 

    virtual ~Piece(); 

    virtual void GetPiece(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE]) const = 0;

    void ClearPiece(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE]) const;

    virtual Color GetColor() const = 0;

};
