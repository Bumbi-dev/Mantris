#include <iostream>
#include <atomic>
#include <thread>
#include "Utils.h"
#include "Game_Interface.h"
#include "O_Piece.h"
#include "I_Piece.h"
#include "T_Piece.h"
#include "S_Piece.h"

using namespace std;

bool game_over = false;

int fall_delay = 100;

thread t;
atomic<bool> ready(false);

void FinishGame()
{
    game_over = true;
}

void SpawnRandomPiece()
{
    bool end_game = false;
    int random_piece = GetRandomValue(0, 3);
    switch(random_piece) {
        case 0:
            end_game = SpawnPiece(S_Piece());
            break;
        case 1:
            end_game = SpawnPiece(T_Piece());
            break;
        case 2:
            end_game = SpawnPiece(I_Piece());
            break;
        case 3:
            end_game = SpawnPiece(O_Piece());
            break;
    }
    if(end_game)
        FinishGame();
}

void UpdateFall() 
{
    while(!game_over) {
        this_thread::sleep_for(chrono::milliseconds(fall_delay));
        
        if(!PieceFalls())
            SpawnRandomPiece();
    }
}

void InitLayout()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Manu Tetris");
    SetTargetFPS(60);
    SetWindowIcon(LoadImage("res/icon.png"));

    BeginDrawing();

    ClearBackground(BACKGROUND);
    ClearGrid();
    SpawnRandomPiece();
    DrawGrid();

    EndDrawing();

    t = thread(UpdateFall);

}

void UpdateGame()
{
    BeginDrawing();

    if(game_over) {
        DrawGrid();
        EndDrawing();
        return;
    }

    if(IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A))
        MovePiece(LEFT);
    if(IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D))
        MovePiece(RIGHT);

    DrawGrid();

    EndDrawing();
}

void StartGame()
{
    InitLayout();
    
    while (!WindowShouldClose())
        UpdateGame();

    CloseWindow();
}