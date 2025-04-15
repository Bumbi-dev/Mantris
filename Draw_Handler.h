#pragma once

#include "Piece.h"

extern Color grid_triangles[GRID_SIZE][GRID_SIZE];
extern bool active_piece[PIECE_SIZE/2][PIECE_SIZE];

extern int active_piece_x;
extern int active_piece_y;
extern int active_piece_rotation;

Color GetTriangle(int y, int x);

Color GetActivePieceTriangle(int i, int j);

void ClearGrid();

void DrawGrid();

void DrawScore(int score);

void DeletePieceGrid();

void DrawPieceGrid(Piece *piece);

void DeleteTopLine(int i);

void DeleteBottomLine(int i);

void DrawEndGameScreen();

void DeleteRows(int i);