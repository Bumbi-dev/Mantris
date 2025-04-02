#include <vector>
#include <iostream>
#include "Utils.h"
#include "Square.h"
using namespace std;

Color grid_triangles[GRID_SIZE][GRID_SIZE];
bool active_piece[PIECE_SIZE/2][PIECE_SIZE];
int active_piece_x = 0;
int active_piece_y = 0;
Color active_piece_color;

bool game_over = false;

bool AreColorsEqual(Color color1, Color color2) {
    if(color1.r != color2.r)
        return false;
    if(color1.g != color2.g)
        return false;
    if(color1.b != color2.b)
        return false;
    if(color1.a != color2.a)
        return false;

    return true;
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
    DrawLeftTriangle(x, y, grid_triangles[i][j*2]);    
    
    x += TRIANGLE_PADDING;
    y -= TRIANGLE_PADDING;
    DrawRightTriangle(x, y, grid_triangles[i][j*2 + 1]);
}

void DrawGrid() 
{
    //GRID BACKGROUND
    DrawRectangle(GRID_X, GRID_Y, BACKGROUND_WIDTH, BACKGROUND_HEIGHT, GRID_BACKGROUND);

    for(int i = 0; i < GRID_SIZE; i++)
        for(int j = 0; j < GRID_SIZE / 2; j++) 
            DrawGridTriangle(i, j);
}

void SpawnPiece(const Piece &piece) 
{
    piece.GetPiece(active_piece);
    active_piece_color = piece.GetColor();

    for(int i = 0; i < PIECE_SIZE/2; i++) 
        for(int j = 0; j < PIECE_SIZE; j++)
            if(active_piece[i][j]) {
                grid_triangles[i][j + (GRID_SIZE - PIECE_SIZE)/2] = active_piece_color;

                if(!AreColorsEqual(grid_triangles[i][j + (GRID_SIZE - PIECE_SIZE)/2], GRID_TRIANGLE))
                    game_over = true;
            }
}

void InitLayout()
{
    ClearBackground(BACKGROUND);

    for(int i = 0; i < GRID_SIZE; i++)
        for(int j = 0; j < GRID_SIZE; j++)
            grid_triangles[i][j] = GRID_TRIANGLE;

    SpawnPiece(Square());

    DrawGrid();
}

void MovePiece() 
{ 
    for(int i = 0; i < PIECE_SIZE/2; i++) 
        for(int j = 0; j < PIECE_SIZE; j++) {
            if(!active_piece[i][j])
                continue;
            if(i + active_piece_y + 2 > GRID_SIZE)
                return;

            grid_triangles[i + active_piece_y][j + (GRID_SIZE - PIECE_SIZE)/2] = GRID_TRIANGLE;
        }
    
    active_piece_y++;

    for(int i = 0; i < PIECE_SIZE/2; i++)
        for(int j = 0; j < PIECE_SIZE; j++)
            if(active_piece[i][j])
                grid_triangles[i + active_piece_y][j + (GRID_SIZE - PIECE_SIZE)/2] = active_piece_color;
}

void UpdateGame()
{
    MovePiece();
    DrawGrid();
}

