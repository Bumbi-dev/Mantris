#include "Draw_Handler.h"

#include "Canvas_Draw_Handler.h"

Color canvas_triangles[GRID_SIZE][CANVAS_GRID_ROWS];

int CANVAS_GRID_WIDTH = TRIANGLE_PADDING + (2 * TRIANGLE_PADDING + TRIANGLE_SIDE) * CANVAS_GRID_ROWS / 2;
int CANVAS_GRID_X = (WINDOW_WIDTH * 2 - CANVAS_GRID_WIDTH) / 2;

void ClearGridCanvas()
{
    for(int i = 0; i < GRID_SIZE; i++)
        for(int j = 0; j < CANVAS_GRID_ROWS; j++)
            canvas_triangles[i][j] = GRID_TRIANGLE;
}
void FillGridCanvas()
{
    for(int i = 0; i < GRID_SIZE; i++)
        for(int j = 0; j < CANVAS_GRID_ROWS; j++)
            canvas_triangles[i][j] = GetRandomColor();
}

void DrawGridTriangleCanvas(int i, int j)
{
    int x = CANVAS_GRID_X + TRIANGLE_PADDING + j * (2 * TRIANGLE_PADDING + TRIANGLE_SIDE);
    int y = GRID_Y + 2 * TRIANGLE_PADDING + i * (2 * TRIANGLE_PADDING + TRIANGLE_SIDE);
    DrawLeftTriangle(x, y, canvas_triangles[i][j*2]);    
    
    x += TRIANGLE_PADDING;
    y -= TRIANGLE_PADDING;
    DrawRightTriangle(x, y, canvas_triangles[i][j*2 + 1]);
}

void DrawGridCanvas()
{
    DrawRectangle(CANVAS_GRID_X, GRID_Y, CANVAS_GRID_WIDTH, BACKGROUND_HEIGHT, GRID_BACKGROUND);

    for(int i = 0; i < GRID_SIZE; i++)
        for(int j = 0; j < CANVAS_GRID_ROWS / 2; j++) 
            DrawGridTriangleCanvas(i, j);
}