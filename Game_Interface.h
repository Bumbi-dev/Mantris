#pragma once
#include "raylib.h"
#include "Piece.h"

enum Direction {
    LEFT,
    RIGHT,
    DOWN
};

Color GetTriangle(int i, int j);

bool AreColorsEqual(Color color1, Color color2);

void ClearGrid();

void DrawGrid();

bool SpawnPiece(Piece &piece);

bool PieceFalls();

bool MovePiece(Direction direction);

void RotatePiece();
