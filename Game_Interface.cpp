#include "Utils.h"

#include "Game_Interface.h"
 
using namespace std;

Piece *piece;

//Return if piece spawned
bool SpawnPiece(Piece &p)
{
    piece = &p;

    active_piece_x = (GRID_SIZE - PIECE_SIZE)/2;
    active_piece_y = 0;
    active_piece_rotation = 0;

    piece->GetPiece(active_piece, active_piece_rotation);

    bool end_game = false;

    for(int i = 0; i < PIECE_SIZE/2; i++) 
        for(int j = 0; j < PIECE_SIZE; j++) {
            if(!active_piece[i][j])
                continue;

            if(!AreColorsEqual(GetTriangle(i, j + active_piece_x), GRID_TRIANGLE))
                end_game = true;
        }   

    DrawPieceGrid(piece);

    return end_game;
}

//Return if piece fell
bool PieceFalls()
{ 
    //Checks for collision
    for(int i = PIECE_SIZE/2 - 1; i >= 0; i--) 
        for(int j = 0; j < PIECE_SIZE; j+=2) {
            if(!(active_piece[i][j] || active_piece[i][j+1]) || (active_piece[i+1][j] || active_piece[i+1][j+1]))
                continue;

            //Check if it reached bottom or is blocked
            if(!AreColorsEqual(GetActivePieceTriangle(i + 1, j+1), GRID_TRIANGLE)
                || i + active_piece_y + 1 >= GRID_SIZE)
                return false;

            //Check the compatible piece is blocked
            if(!AreColorsEqual(GetActivePieceTriangle(i + 1, j), GRID_TRIANGLE)
                && active_piece[i][j])
                return false;

            //Check if it shares the same square with another piece
            if(!AreColorsEqual(GetActivePieceTriangle(i, j), GRID_TRIANGLE)
                && active_piece[i][j+1] && !active_piece[i][j])
                return false;
        }
    
    DeletePieceGrid();

    active_piece_y++;

    DrawPieceGrid(piece);

    return true;
}

//Return if piece moved
bool MovePiece(Direction direction)
{
    int x_offset;

    if(direction == LEFT)
    {
        x_offset = -2;

        //If the piece reaches the left limit
        for(int i = 0; i < PIECE_SIZE / 2; i++) {
            if(!active_piece[i][0] && !active_piece[i][1])  
                continue;

            if(active_piece_x + x_offset < 0)
                return false;

            if(!AreColorsEqual(GetActivePieceTriangle(i,-1), GRID_TRIANGLE)
                || !AreColorsEqual(GetActivePieceTriangle(i,-2), GRID_TRIANGLE))
                    return false;
        }

        for(int j = 2; j < PIECE_SIZE && x_offset != 0; j+=2) 
            for(int i = 0; i < PIECE_SIZE/2 && x_offset != 0; i++) 
            {
                if(!(active_piece[i][j] || active_piece[i][j+1]) || (active_piece[i][j-2] || active_piece[i][j-1])) 
                    continue;

                //Checks for border, or blocking piece
                if(!AreColorsEqual(GetActivePieceTriangle(i, j-1), GRID_TRIANGLE)
                    || j + active_piece_x + x_offset < 0)
                    return false;

                //Checks if the lower piece would collide
                if(!AreColorsEqual(GetActivePieceTriangle(i, j-2), GRID_TRIANGLE)
                    && active_piece[i][j])
                    return false;

                //Check if it shares the same square with another piece
                if(!AreColorsEqual(GetActivePieceTriangle(i, j), GRID_TRIANGLE)
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
                if(!AreColorsEqual(GetActivePieceTriangle(i, j+2), GRID_TRIANGLE)
                    || j + active_piece_x + x_offset >= GRID_SIZE)
                    return false;

                //Checks if the lower piece would collide
                if(!AreColorsEqual(GetActivePieceTriangle(i, j+3), GRID_TRIANGLE)
                    && active_piece[i][j+1])
                    return false;

                //Check if it shares the same square with another piece
                if(!AreColorsEqual(GetActivePieceTriangle(i, j+1), GRID_TRIANGLE)
                    && active_piece[i][j] && !active_piece[i][j+1])
                    return false;
            }
    }

    DeletePieceGrid();

    active_piece_x += x_offset;

    DrawPieceGrid(piece);

    return true;
}

void RotatePiece()
{
    active_piece_rotation++;

    DeletePieceGrid();
    piece->GetPiece(active_piece, active_piece_rotation);

    for(int i = PIECE_SIZE/2 - 1; i >= 0; i--) 
        for(int j = 0; j < PIECE_SIZE; j++) 
        {
            if(!active_piece[i][j])
                continue;

            //Reverts rotation
            if(!AreColorsEqual(GetActivePieceTriangle(i, j), GRID_TRIANGLE)
                || j + active_piece_x >= GRID_SIZE || j + active_piece_x < 0) 
            {
                active_piece_rotation--;
                if(active_piece_rotation < 0)
                    active_piece_rotation = 3;

                piece->GetPiece(active_piece, active_piece_rotation);

                DrawPieceGrid(piece);
                return;
            }  
        }

    DrawPieceGrid(piece);
}

//Return number of deleted lines
int DeleteCompletedLines()
{
    bool top_complete;
    bool bottom_complete;
    int lines_completed = 0;

    for(int i = GRID_SIZE - 1; i >= 0; i--)  {
        top_complete = true;
        bottom_complete = true;
        for(int j = 0; j < GRID_SIZE; j+=2) {
            if(AreColorsEqual(grid_triangles[i][j], GRID_TRIANGLE))
                bottom_complete = false;
            if(AreColorsEqual(grid_triangles[i][j+1], GRID_TRIANGLE))
                top_complete = false;
        }

        if(top_complete) {
            DeleteTopLine(i);
            lines_completed++;
        }
        if(bottom_complete) {
            DeleteBottomLine(i);
            lines_completed++;
        }

        if(!top_complete && !bottom_complete)
            continue;

        DeleteRows(i);

        i++; //Checks again for more completions
    }

    return lines_completed;
}