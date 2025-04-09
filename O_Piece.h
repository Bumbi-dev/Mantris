#pragma once
#include "Piece.h"

class O_Piece : public Piece 
{
public:
    Color GetColor() const override;
    void GetPiece(bool (&triangles)[PIECE_SIZE/2][PIECE_SIZE], int pos) const override;
};