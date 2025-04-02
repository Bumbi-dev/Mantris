#pragma once
#include "Piece.h"

class Square : public Piece {
public:
    Square();
    Color color;
    Color GetColor();
    void GetPiece(Color (&triangles)[8][8]);
};