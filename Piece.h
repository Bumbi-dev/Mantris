#pragma once
#include <raylib.h> 

class Piece {
public:
    Piece(); 

    virtual ~Piece(); 

    virtual void GetPiece(Color (&triangles)[8][8]) = 0;

    void ClearPiece(Color (&triangles)[8][8]) const;

    virtual Color GetColor() = 0;

};
