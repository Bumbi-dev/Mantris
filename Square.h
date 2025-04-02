#pragma once
#include "Piece.h"

class Square : public Piece 
{
public:
    Square();
    Color color;
    Color GetColor() const override;
    void GetPiece(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE]) const override;
};