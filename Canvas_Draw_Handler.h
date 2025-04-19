#pragma once

#include "Utils.h"

constexpr int GRID_MULTIPLIER = 3;
constexpr int CANVAS_GRID_ROWS = GRID_SIZE * GRID_MULTIPLIER + 4;

extern Color canvas_triangles[GRID_SIZE][CANVAS_GRID_ROWS];

void ClearGridCanvas();

void DrawGridCanvas();

void DrawGridTriangleCanvas(int i, int j);
