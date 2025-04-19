#include "Canvas_Draw_Handler.h"

#include "Canvas.h"

using namespace std;

int i, j;
bool first_time = true;

void UpdateTrianglePosition()
{
    int x = GetMouseX();
    int y = GetMouseY();

    i = (y - GRID_Y - 2 * TRIANGLE_PADDING) / (2 * TRIANGLE_PADDING + TRIANGLE_SIDE);

    int squareIndex = (x - GRID_X - TRIANGLE_PADDING) / (2 * TRIANGLE_PADDING + TRIANGLE_SIDE);
    int baseX = GRID_X + TRIANGLE_PADDING + squareIndex * (2 * TRIANGLE_PADDING + TRIANGLE_SIDE);
    int baseY = GRID_Y + 2 * TRIANGLE_PADDING + i * (2 * TRIANGLE_PADDING + TRIANGLE_SIDE);

    bool isRightTriangle = (y < baseY + x - baseX);

    j = squareIndex * 2 + (isRightTriangle ? 1 : 0);
}

void UpdateGridTriangle()
{
    UpdateTrianglePosition();

    if(i < 0 || j < 0 || j > CANVAS_GRID_ROWS - 1 || i > GRID_SIZE - 1)
        return;

    if(first_time)
        return;

    if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) 
        canvas_triangles[i][j] = GetRandomColor();
    
    if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        canvas_triangles[i][j] = GRID_TRIANGLE;
}

void UpdateGrid()
{
    UpdateGridTriangle();

    if(IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
        ClearGridCanvas();
}

void UpdateCanvas()
{
    ClearBackground(BACKGROUND);

    UpdateGrid();

    DrawGridCanvas();
}

void InitCanvas()
{
    BeginDrawing();
    ClearBackground(BACKGROUND);
    EndDrawing();

    SetWindowSize(WINDOW_WIDTH * 2, WINDOW_HEIGHT);

    //Center the window
    SetWindowPosition(GetWindowPosition().x - WINDOW_WIDTH / 2, GetWindowPosition().y);

    ClearGridCanvas();
}

void StartCanvas()
{
    InitCanvas();

    while (!WindowShouldClose()) {
        BeginDrawing();

        UpdateCanvas();

        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            first_time = false;

        EndDrawing();
    }
}