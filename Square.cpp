#include <raylib.h>
#include "Square.h"
#include "Utils.h"
#include <iostream>

using namespace std;

Square::Square() {
    color = ACTIVE_PIECE;
}

Color Square::GetColor() {
    return color;
}

void Square::GetPiece(Color (&triangles)[8][8]) {
    ClearPiece(triangles);
    triangles[3][0] = color;
    triangles[4][0] = color;
}
