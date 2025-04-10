#include "Game_Interface.h"
#include "Utils.h"

using namespace std;

Color grid_triangles[GRID_SIZE][GRID_SIZE];
bool active_piece[PIECE_SIZE/2][PIECE_SIZE];

Piece* piece;

int active_piece_x;
int active_piece_y;
int active_piece_rotation;

int score;

Color GetTriangle(int y, int x)
{
    return grid_triangles[y][x];
}
Color GetActivePieceTriangle(int i, int j)//TODO implement this where needed
{
    return grid_triangles[i + active_piece_y][j + active_piece_x];
}

void UpdateScore(int s)
{
    score = s;

    int text_width = MeasureText("SCORE", 30);
    DrawText("SCORE", SCORE_BOX_X + SCORE_BOX_WIDTH / 2 - text_width / 2, SCORE_BOX_Y + 40, 30, WHITE);

    text_width = MeasureText(TextFormat("%d", score), 40);
    DrawText(TextFormat("%d", score), SCORE_BOX_X + SCORE_BOX_WIDTH / 2 - text_width / 2, SCORE_BOX_Y + 120, 30, WHITE);
}

void DrawScoreBox()
{
    DrawRectangleRounded(
        (Rectangle){SCORE_BOX_X, SCORE_BOX_Y, SCORE_BOX_WIDTH, SCORE_BOX_HEIGHT},
        0.3f, 8, SCORE_BOX_BACKGROUND);

    UpdateScore(0);
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

bool SpawnPiece(Piece &p)
{
    piece = &p;
    active_piece_x = (GRID_SIZE - PIECE_SIZE)/2;
    active_piece_y = 0;
    active_piece_rotation = 0;
    piece->GetPiece(active_piece, 0);

    bool end_game = false;
    //TODO make this a function
    for(int i = 0; i < PIECE_SIZE/2; i++) 
        for(int j = 0; j < PIECE_SIZE; j++) {
            if(!active_piece[i][j])
                continue;

            if(!AreColorsEqual(grid_triangles[i][j + active_piece_x], GRID_TRIANGLE))
                end_game = true;
                
            grid_triangles[i][j + active_piece_x] = piece->GetColor();
        }   

    return end_game;
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
                grid_triangles[i + active_piece_y][j + active_piece_x] = piece->GetColor();
}

bool PieceFalls()
{ 
    //Checks for collision
    for(int i = PIECE_SIZE/2 - 1; i >= 0; i--) 
        for(int j = 0; j < PIECE_SIZE; j+=2) {
            if(!(active_piece[i][j] || active_piece[i][j+1]) || (active_piece[i+1][j] || active_piece[i+1][j+1]))
                continue;

            //TODO maybe remove this to make game easier
            //Check if it reached bottom or is blocked
            if(!AreColorsEqual(grid_triangles[i + active_piece_y + 1][j + active_piece_x + 1], GRID_TRIANGLE)
                || i + active_piece_y + 1 >= GRID_SIZE)
                return false;

            //Check the compatible piece is blocked
            if(!AreColorsEqual(grid_triangles[i + active_piece_y + 1][j + active_piece_x], GRID_TRIANGLE)
                && active_piece[i][j])
                return false;

            //Check if it shares the same square with another piece
            if(!AreColorsEqual(grid_triangles[i + active_piece_y][j + active_piece_x], GRID_TRIANGLE)
                && active_piece[i][j+1] && !active_piece[i][j])
                return false;
        }
    
    DeletePiece();

    active_piece_y++;

    DrawPiece();

    return true;
}

bool MovePiece(Direction direction)
{
    int x_offset;

    if(direction == LEFT)
    {
        x_offset = -2;

        for(int i = 0; i < PIECE_SIZE; i++)
            if(active_piece[i][0] && active_piece_x + x_offset < 0)  
                return false;

        //TODO maybe make conditions less strict so that you can insert easier
        for(int j = 2; j < PIECE_SIZE && x_offset != 0; j+=2) 
            for(int i = 0; i < PIECE_SIZE/2 && x_offset != 0; i++) 
            {
                if(!(active_piece[i][j] || active_piece[i][j+1]) || (active_piece[i][j-2] || active_piece[i][j-1])) 
                    continue;

                //Checks for border, or blocking piece
                if(!AreColorsEqual(grid_triangles[i + active_piece_y][j + active_piece_x-1], GRID_TRIANGLE)
                    || j + active_piece_x + x_offset < 0)
                    return false;

                //Checks if the lower piece would collide
                if(!AreColorsEqual(grid_triangles[i + active_piece_y][j + active_piece_x-2], GRID_TRIANGLE)
                    && active_piece[i][j])
                    return false;

                //Check if it shares the same square with another piece
                if(!AreColorsEqual(grid_triangles[i + active_piece_y][j + active_piece_x], GRID_TRIANGLE)
                    && active_piece[i][j+1] && !active_piece[i][j])
                    return false;
            }
    }

    if(direction == RIGHT) {
        x_offset = 2;

        for(int j = 2; j < PIECE_SIZE && x_offset != 0; j+=2) 
            for(int i = 0; i < PIECE_SIZE/2 && x_offset != 0; i++) 
            {
                if(!(active_piece[i][j] || active_piece[i][j+1]) || (active_piece[i][j+2] || active_piece[i][j+3])) 
                    continue;

                //Checks for border, or blocking piece
                if(!AreColorsEqual(grid_triangles[i + active_piece_y][j + active_piece_x + 2], GRID_TRIANGLE)
                    || j + active_piece_x + x_offset >= GRID_SIZE)
                    return false;

                //Checks if the lower piece would collide
                if(!AreColorsEqual(grid_triangles[i + active_piece_y][j + active_piece_x + 3], GRID_TRIANGLE)
                    && active_piece[i][j+1])
                    return false;

                //Check if it shares the same square with another piece
                if(!AreColorsEqual(grid_triangles[i + active_piece_y][j + active_piece_x + 1], GRID_TRIANGLE)
                    && active_piece[i][j] && !active_piece[i][j+1])
                    return false;
            }
    }

    DeletePiece();

    active_piece_x += x_offset;

    DrawPiece();

    return true;
}

void RotatePiece()
{
    active_piece_rotation++;
    active_piece_rotation %= 4;

    DeletePiece();//TODO draw after checking 
    piece->GetPiece(active_piece, active_piece_rotation);

    for(int i = PIECE_SIZE/2 - 1; i >= 0; i--) 
        for(int j = 0; j < PIECE_SIZE; j++) 
        {
            if(!active_piece[i][j])
                continue;

            //TODO if the piece is L try moving it to the left or right
            //Reverts rotation
            if(!AreColorsEqual(grid_triangles[i + active_piece_y][j + active_piece_x], GRID_TRIANGLE)
                || j + active_piece_x >= GRID_SIZE || j + active_piece_x < 0) 
            {
                active_piece_rotation--;
                if(active_piece_rotation < 0)
                    active_piece_rotation = 3;

                piece->GetPiece(active_piece, active_piece_rotation);

                DrawPiece();
                return;
            }  
        }
    DrawPiece();
}
