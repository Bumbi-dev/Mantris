#pragma once
#include "Piece.h"

class Square_Piece : public Piece 
{
public:
    Square_Piece();
    Color color;
    Color GetColor() const override;
    void GetPiece(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE]) const override;
};