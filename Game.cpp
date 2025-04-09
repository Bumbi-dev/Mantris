#include <atomic>
#include <thread>
#include <chrono>
#include "Utils.h"
#include "Game_Interface.h"
#include "I_Piece.h"
#include "L_Piece.h"
#include "O_Piece.h"
#include "P_Piece.h"
#include "T_Piece.h"
#include "V_Piece.h"
#include "N_Piece.h"

using namespace std;
using namespace chrono;

bool game_over = false;
int fall_delay = 300;

steady_clock::time_point last_move;

thread t;
atomic<bool> ready(false);

Piece* pieces[10] = {new I_Piece(), new O_Piece(), new V_Piece(), new P_Piece(), new T_Piece(), new L_Piece(), new N_Piece()};

void FinishGame()
{
    game_over = true;
}

void SpawnRandomPiece()
{
    int random_piece = GetRandomValue(0, 6);
    
    bool end_game = SpawnPiece(*pieces[random_piece]);

    if(end_game)
        FinishGame();
}

void UpdateMove()
{
    //TODO maybe fix when adding key_s to the condition it may happen with both key_down and key_s at the same time
    if(IsKeyPressed(KEY_DOWN))
        fall_delay /= 2;
    if(IsKeyReleased(KEY_DOWN))
        fall_delay *= 2;

    if(IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W))
        RotatePiece();

    int time_since_last_move = duration_cast<milliseconds>(steady_clock::now() - last_move).count();

    if(time_since_last_move < 100)
        return;

    if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
        if(MovePiece(LEFT))
            last_move = steady_clock::now();

    if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
        if(MovePiece(RIGHT))
            last_move = steady_clock::now();
}

void UpdateFall() 
{
    while(!game_over) {

        while(IsKeyDown(KEY_SPACE))
            this_thread::sleep_for(chrono::milliseconds(1));

        this_thread::sleep_for(chrono::milliseconds(fall_delay));
        
        
        if(!PieceFalls())
            SpawnRandomPiece();
    }
}

void UpdateGame()
{
    BeginDrawing();

    if(game_over) {
        DrawGrid();
        EndDrawing();
        return;
    }

    UpdateMove();
    
    DrawGrid();

    EndDrawing();
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

    last_move = steady_clock::now();

    t = thread(UpdateFall);
}

void StartGame()
{
    InitLayout();
    
    while (!WindowShouldClose())
        UpdateGame();

    CloseWindow();
}