#pragma once
#include "raylib.h"
#include "Piece.h"

enum Direction {
    LEFT,
    RIGHT,
    DOWN
};

void UpdateScore(int score);

void ClearGrid();

void DrawGrid();

bool SpawnPiece(Piece &piece);

bool PieceFalls();

bool MovePiece(Direction direction);

void RotatePiece();

int DeleteCompletedLines();