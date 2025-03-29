#include<vector>
#include<raylib.h>
#include<Utils.cpp>
#include<Piece.cpp>

#include<iostream>
using namespace std;
Color triangle_colors[16][16];

void PrintColor(const Color& color) {
    std::cout << "(" 
              << (int)color.r << ", " 
              << (int)color.g << ", " 
              << (int)color.b << ", " 
              << (int)color.a << ")";
}

void DrawLeftTriangle(float x, float y, Color color)
{
    Vector2 v1 = {x, y };
    Vector2 v2 = {x, y + TRIANGLE_SIDE};
    Vector2 v3 = {x + TRIANGLE_SIDE, y + TRIANGLE_SIDE};

    DrawTriangle(v1, v2, v3, color);
}

void DrawRightTriangle(float x, float y, Color color)
{
    Vector2 v1 = {x, y };
    Vector2 v2 = {x + TRIANGLE_SIDE, y + TRIANGLE_SIDE};
    Vector2 v3 = {x + TRIANGLE_SIDE, y};

    DrawTriangle(v1, v2, v3, color);
}

void DrawGridTriangle(int i, int j) 
{
    int x = GRID_X + TRIANGLE_PADDING + j * (2 * TRIANGLE_PADDING + TRIANGLE_SIDE);
    int y = GRID_Y + 2 * TRIANGLE_PADDING + i * (2 * TRIANGLE_PADDING + TRIANGLE_SIDE);
    DrawLeftTriangle(x, y, triangle_colors[i][j*2]);    
    
    x += TRIANGLE_PADDING;
    y -= TRIANGLE_PADDING;
    DrawRightTriangle(x, y, triangle_colors[i][j*2 + 1]);
}

void DrawGrid() 
{
    //GRID BACKGROUND
    DrawRectangle(GRID_X, GRID_Y, BACKGROUND_WIDTH, BACKGROUND_HEIGHT, GRID_BACKGROUND);

    for(int i = 0; i < 16; i++)
        for(int j = 0; j < 8; j++) 
            DrawGridTriangle(i, j);
}

void InitLayout()
{
    ClearBackground(BACKGROUND);

    for(int i = 0; i < 16; i++)
        for(int j = 0; j < 32; j++)
            triangle_colors[i][j] = GRID_TRIANGLE;

    DrawGrid();
}

void SpawnPiece(int i, int j, Piece piece) {
    cout << "spawn";
}

void UpdateGame()
{
    // DrawGrid();
    SpawnPiece(5, 5, Piece());
}
