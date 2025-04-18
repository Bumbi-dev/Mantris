#include "Draw_Handler.h"

Color grid_triangles[GRID_SIZE][GRID_SIZE];
bool active_piece[PIECE_SIZE/2][PIECE_SIZE];

int active_piece_x; 
int active_piece_y;
int active_piece_rotation;

void SetTriangle(int y, int x, Color color)
{
    grid_triangles[y][x] = color;
}
Color GetTriangle(int y, int x)
{
    return grid_triangles[y][x];
}

Color GetActivePieceTriangle(int y, int x)
{
    return GetTriangle(y + active_piece_y, x + active_piece_x);
}

void ClearGrid()
{
    for(int i = 0; i < GRID_SIZE; i++)
        for(int j = 0; j < GRID_SIZE; j++)
            grid_triangles[i][j] = GRID_TRIANGLE;
}

void DrawLeftTriangle(float x, float y, Color color)
{
    Vector2 v1 = {x, y};
    Vector2 v2 = {x, y + TRIANGLE_SIDE};
    Vector2 v3 = {x + TRIANGLE_SIDE, y + TRIANGLE_SIDE};

    if(AreColorsEqual(color, GRID_TRIANGLE))
    {
        color = DARKER_GRID_TRIANGLE;
        DrawTriangle(v1, v2, v3, color);
        return;
    }

    Color border_color = GetDarkerColor(color);
    DrawTriangle(v1, v2, v3, border_color);

    v1 = {x + 3, y + 8};
    v2 = {x + 3, y + TRIANGLE_SIDE - 3};       
    v3 = {x + TRIANGLE_SIDE - 8, y + TRIANGLE_SIDE - 3};

    DrawTriangle(v1, v2, v3, color);
}

void DrawRightTriangle(float x, float y, Color color)
{
    Vector2 v1 = {x, y };
    Vector2 v2 = {x + TRIANGLE_SIDE, y + TRIANGLE_SIDE};
    Vector2 v3 = {x + TRIANGLE_SIDE, y};

    Color border_color = GetDarkerColor(color);

    DrawTriangle(v1, v2, v3, border_color);

    v1 = {x + 8 , y + 3};
    v2 = {x + TRIANGLE_SIDE - 3, y + TRIANGLE_SIDE - 8};
    v3 = {x + TRIANGLE_SIDE - 3, y + 3};

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

void DrawScore(int score)
{    
    DrawRectangleRounded(
        (Rectangle){SCORE_BOX_X, SCORE_BOX_Y, SCORE_BOX_WIDTH, SCORE_BOX_HEIGHT},
        0.3f, 8, SCORE_BOX_BACKGROUND);

    int text_width = MeasureText("SCORE", 30);
    DrawText("SCORE", SCORE_BOX_X + SCORE_BOX_WIDTH / 2 - text_width / 2, SCORE_BOX_Y + 40, 30, WHITE);

    text_width = MeasureText(TextFormat("%d", score), 40);
    DrawText(TextFormat("%d", score), SCORE_BOX_X + SCORE_BOX_WIDTH / 2 - text_width / 2, SCORE_BOX_Y + 120, 30, WHITE);
}

void DeletePieceGrid()
{
    for(int i = 0; i < PIECE_SIZE/2; i++) 
        for(int j = 0; j < PIECE_SIZE; j++) {
            if(!active_piece[i][j])
                continue;

            grid_triangles[i + active_piece_y][j + active_piece_x] = GRID_TRIANGLE;
        }
}

void DrawPieceGrid(Piece *piece)
{
    for(int i = 0; i < PIECE_SIZE/2; i++)
        for(int j = 0; j < PIECE_SIZE; j++)
            if(active_piece[i][j])
                grid_triangles[i + active_piece_y][j + active_piece_x] = piece->GetColor();
}

void DeleteTopLine(int i) 
{
    for(int j = 0; j < GRID_SIZE; j+=2)
        grid_triangles[i][j+1] = GRID_TRIANGLE;
}

void DeleteBottomLine(int i) 
{
    for(int j = 0; j < GRID_SIZE; j+=2)
        grid_triangles[i][j] = GRID_TRIANGLE;
}

void DrawEndGameScreen() 
{
    DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, {0, 0, 0, 147});

    int text_width = MeasureText("GAME OVER", 70);
    DrawText("GAME OVER", (WINDOW_WIDTH - text_width) / 2, WINDOW_HEIGHT / 2 - 20, 70, WHITE);

    text_width = MeasureText("Press Space to continue", 20);
    DrawText("Press Space to continue", (WINDOW_WIDTH - text_width) / 2, WINDOW_HEIGHT / 2 + 60, 20, WHITE);
}

void DeleteRows(int i)
{
    for(int j = 0; j < GRID_SIZE; j+=2)
        if(AreColorsEqual(grid_triangles[i][j], GRID_TRIANGLE) && AreColorsEqual(grid_triangles[i][j+1], GRID_TRIANGLE))
            for(int k = i; k > 0; k--) {
                grid_triangles[k][j] = grid_triangles[k-1][j];
                grid_triangles[k][j+1] = grid_triangles[k-1][j+1];
            }
}