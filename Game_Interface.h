#pragma once
#include "raylib.h"
#include "Piece.h"

enum Direction {
    LEFT,
    RIGHT,
    DOWN
};

void UpdateScore(int s);

void DrawScoreBox();

void ClearGrid();

void DrawGrid();

bool SpawnPiece(Piece &piece);

bool PieceFalls();

bool MovePiece(Direction direction);

void RotatePiece();

void DeleteCompletedLines();