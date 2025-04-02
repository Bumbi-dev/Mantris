#include<raylib.h>
#include "Utils.h"

const int TRIANGLE_SIDE = 55;
const int TRIANGLE_PADDING = 1;
const int BACKGROUND_WIDTH = TRIANGLE_PADDING + (2 * TRIANGLE_PADDING + TRIANGLE_SIDE) * 8;
const int BACKGROUND_HEIGHT = TRIANGLE_PADDING + (2 * TRIANGLE_PADDING + TRIANGLE_SIDE) * 16;

const int GRID_X = 10;
const int GRID_Y = 10;

const Color BACKGROUND = {48, 25, 52, 255};
const Color GRID_BACKGROUND = {34, 49, 59, 255};
const Color GRID_TRIANGLE = {23, 23, 23, 255};
const Color ACTIVE_PIECE = {44, 123, 72, 255};
