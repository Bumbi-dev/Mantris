#include<raylib.h>

int const TRIANGLE_SIDE = 55;
int const TRIANGLE_PADDING = 1;
int const BACKGROUND_WIDTH = TRIANGLE_PADDING + (2 * TRIANGLE_PADDING + TRIANGLE_SIDE) * 8;
int const BACKGROUND_HEIGHT = TRIANGLE_PADDING + (2 * TRIANGLE_PADDING + TRIANGLE_SIDE) * 16;

int const GRID_X = 10;
int const GRID_Y = 10;

Color const BACKGROUND = {48, 25, 52, 255};
Color const GRID_BACKGROUND = {34, 49, 59, 255};
Color const GRID_TRIANGLE = {23, 23, 23, 255};
Color const ACTIVE_PIECE = {44, 123, 72, 255};

bool const SQUARE_PIECE[1][2] = {{true, true}};
bool const LONG_PIECE[4][2] = {{true,true}, {true,true}, {true,true}, {true,true}};

