#include <vector>
#include <iostream>
#include "Utils.h"
#include "Square_Piece.h"
#include "Line_Piece.h"
#include "T_Piece.h"
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

void FinishGame()
{
    game_over = true;
}

void SpawnPiece(const Piece &piece) 
{
    active_piece_x = (GRID_SIZE - PIECE_SIZE)/2;
    active_piece_y = 0;
    piece.GetPiece(active_piece);
    active_piece_color = piece.GetColor();

    //TODO make this a function
    for(int i = 0; i < PIECE_SIZE/2; i++) 
        for(int j = 0; j < PIECE_SIZE; j++) {
            if(!active_piece[i][j])
                continue;

            if(!AreColorsEqual(grid_triangles[i][j + active_piece_x], GRID_TRIANGLE))
                FinishGame();
                
            grid_triangles[i][j + active_piece_x] = active_piece_color;
        }   
}

void SpawnRandomPiece()
{
    int random_piece = GetRandomValue(0, 2);
    switch(random_piece) {
        case 0:
            SpawnPiece(Square_Piece());
            break;
        case 1:
            SpawnPiece(Line_Piece());
            break;
        case 2:
            SpawnPiece(T_Piece());
            break;
    }
}

void DeletePiece()
{
    for(int i = 0; i < PIECE_SIZE/2; i++) 
        for(int j = 0; j < PIECE_SIZE; j++) {
            if(!active_piece[i][j])
                continue;

            grid_triangles[i + active_piece_y][j + active_piece_x] = GRID_TRIANGLE;
        }
}

void DrawPiece()
{
    for(int i = 0; i < PIECE_SIZE/2; i++)
        for(int j = 0; j < PIECE_SIZE; j++)
            if(active_piece[i][j])
                grid_triangles[i + active_piece_y][j + active_piece_x] = active_piece_color;
}

void InitLayout()
{
    ClearBackground(BACKGROUND);

    for(int i = 0; i < GRID_SIZE; i++)
        for(int j = 0; j < GRID_SIZE; j++)
            grid_triangles[i][j] = GRID_TRIANGLE;

    SpawnRandomPiece();

    DrawGrid();
}

void PieceFalls()
{ 
    //Checks for collision
    for(int i = PIECE_SIZE/2; i >= 1; i--) 
        for(int j = 0; j < PIECE_SIZE; j++) {
            if(!active_piece[i-1][j-1])
                continue;
            
            if((!AreColorsEqual(grid_triangles[i + active_piece_y][j + active_piece_x - 1],
                     GRID_TRIANGLE)
                && !active_piece[i][j])
                || i + active_piece_y + 1 > GRID_SIZE)
            {
                SpawnRandomPiece();
                return;
            }
        }
    
    DeletePiece();

    active_piece_y++;

    DrawPiece();
}

void MovePiece()
{
    DeletePiece();

    if(IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
        active_piece_x -= 2;
    if(IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
        active_piece_x += 2;

    DrawPiece();
}

void UpdateGame()
{
    if(game_over)
        return;

    MovePiece();
    
    PieceFalls();

    DrawGrid();

    WaitTime(0.5f);
}
