#pragma once

#include <raylib.h>
#include <iostream>
#include "Colors.h"

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

constexpr int PIECE_SIZE = 10;

extern Texture2D SECRET_HOME_SCREEN_BACKROUND;
extern Texture2D HOME_SCREEN_BACKROUND;
extern Image ICON;

void LoadAssets();

Color GetRandomColor();
Color GetDarkerColor(Color c);
bool AreColorsEqual(Color color1, Color color2);
