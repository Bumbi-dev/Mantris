#pragma once
#include <raylib.h>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 1000;

constexpr int GRID_SIZE = 18;
constexpr int GRID_X = 10;
constexpr int GRID_Y = 10;
constexpr int TRIANGLE_SIDE = 50;
constexpr int TRIANGLE_PADDING = 1;

constexpr int BACKGROUND_WIDTH = TRIANGLE_PADDING + (2 * TRIANGLE_PADDING + TRIANGLE_SIDE) * GRID_SIZE / 2;
constexpr int BACKGROUND_HEIGHT = TRIANGLE_PADDING + (2 * TRIANGLE_PADDING + TRIANGLE_SIDE) * GRID_SIZE;

constexpr Color BACKGROUND = {48, 25, 52, 255};
constexpr Color GRID_BACKGROUND = {34, 49, 59, 255};
constexpr Color GRID_TRIANGLE = {23, 23, 23, 255};
constexpr Color ACTIVE_PIECE = {44, 123, 72, 255};
constexpr Color SQUARE_COLOR = {240, 220, 5, 255};
constexpr Color LINE_COLOR = {240, 5, 5, 255};
constexpr Color T_COLOR = {5, 240, 5, 255};

constexpr int PIECE_SIZE = 10;