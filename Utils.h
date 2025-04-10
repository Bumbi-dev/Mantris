#pragma once

#include <raylib.h>
#include <iostream>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 1000;

constexpr int GRID_SIZE = 18;
constexpr int GRID_X = 10;
constexpr int GRID_Y = 10;
constexpr int TRIANGLE_SIDE = 50;
constexpr int TRIANGLE_PADDING = 2;

constexpr int BACKGROUND_WIDTH = TRIANGLE_PADDING + (2 * TRIANGLE_PADDING + TRIANGLE_SIDE) * GRID_SIZE / 2;
constexpr int BACKGROUND_HEIGHT = TRIANGLE_PADDING + (2 * TRIANGLE_PADDING + TRIANGLE_SIDE) * GRID_SIZE;

constexpr int SCORE_BOX_X = BACKGROUND_WIDTH + 40;
constexpr int SCORE_BOX_Y = 100;
constexpr int SCORE_BOX_WIDTH = 235;
constexpr int SCORE_BOX_HEIGHT = 180;

constexpr Color BACKGROUND = {7, 7, 31, 255};
constexpr Color GRID_BACKGROUND = {34, 49, 59, 255};
constexpr Color SCORE_BOX_BACKGROUND = {20, 20, 45, 255};
constexpr Color GRID_TRIANGLE = {23, 23, 23, 255};
constexpr Color DARKER_GRID_TRIANGLE = {17, 17, 17, 255};
constexpr Color ACTIVE_PIECE = {44, 123, 72, 255};
constexpr Color O_COLOR = {240, 220, 5, 255};
constexpr Color I_COLOR = {240, 5, 5, 255};
constexpr Color T_COLOR = {5, 240, 5, 255};
constexpr Color P_COLOR = {240, 5, 240, 255};
constexpr Color V_COLOR = {255, 191, 0, 255};
constexpr Color L_COLOR = {5, 240, 240, 255};
constexpr Color N_COLOR = {240, 5, 120, 255};

constexpr int PIECE_SIZE = 10;

Color GetDarkerColor(Color c);
bool AreColorsEqual(Color color1, Color color2);
