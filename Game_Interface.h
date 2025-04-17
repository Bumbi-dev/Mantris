#pragma once
#include "raylib.h"
#include "Piece.h"
#include "Draw_Handler.h"

enum Direction {
    LEFT,
    RIGHT,
    DOWN
};

extern Piece *piece;

bool SpawnPiece(Piece &piece);

bool PieceFalls();

bool MovePiece(Direction direction);

void RotatePiece();

int DeleteCompletedLines();