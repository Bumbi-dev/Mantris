#include "Game_Interface.h"
#include "Utils.h"

Color grid_triangles[GRID_SIZE][GRID_SIZE];
bool active_piece[PIECE_SIZE/2][PIECE_SIZE];

Color active_piece_color;

int active_piece_x = 0;
int active_piece_y = 0;

Color GetTriangle(int i, int j)
{
    return grid_triangles[i][j];
}

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

void ClearGrid()
{
    for(int i = 0; i < GRID_SIZE; i++)
        for(int j = 0; j < GRID_SIZE; j++)
            grid_triangles[i][j] = GRID_TRIANGLE;
}

//TODO add a border slight darker border colored to the triangles
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

bool SpawnPiece(const Piece &piece) 
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
                return true;
                
            grid_triangles[i][j + active_piece_x] = active_piece_color;
        }   

    return false;
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

bool PieceFalls()
{ 
    //Checks for collision
    for(int i = PIECE_SIZE/2 - 1; i >= 0; i--) 
        for(int j = 0; j < PIECE_SIZE; j+=2) {
            if(!(active_piece[i][j] || active_piece[i][j+1]) || (active_piece[i+1][j] || active_piece[i+1][j+1]))
                continue;

            if(!AreColorsEqual(grid_triangles[i + active_piece_y + 1][j + active_piece_x + 1], GRID_TRIANGLE)
                || i + active_piece_y + 1 >= GRID_SIZE)
            {
                return false;
            }

            if(!AreColorsEqual(grid_triangles[i + active_piece_y + 1][j + active_piece_x], GRID_TRIANGLE)
                && active_piece[i][j])
            {
                return false;
            }
            if(!AreColorsEqual(grid_triangles[i + active_piece_y][j + active_piece_x], GRID_TRIANGLE)
                && active_piece[i][j+1] && !active_piece[i][j])
            {
                return false;
            }
        }
    
    DeletePiece();

    active_piece_y++;

    DrawPiece();

    return true;
}

void MovePiece(Direction direction)
{
    DeletePiece();

    if(direction == LEFT)
        active_piece_x -= 2;
    if(direction == RIGHT)
        active_piece_x += 2;;


    if(active_piece_x < 0)
        active_piece_x = 0;
    if(active_piece_x > GRID_SIZE - PIECE_SIZE)//TODO fix this
        active_piece_x = GRID_SIZE - PIECE_SIZE;

    DrawPiece();
}