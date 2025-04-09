#include <atomic>
#include <thread>
#include <chrono>
#include "Utils.h"
#include "Game_Interface.h"
#include "O_Piece.h"
#include "I_Piece.h"
#include "T_Piece.h"
#include "S_Piece.h"
#include "V_Piece.h"
#include "P_Piece.h"

using namespace std;
using namespace chrono;

bool game_over = false;
int fall_delay = 300;

steady_clock::time_point last_move;

thread t;
atomic<bool> ready(false);

Piece* pieces[10] = {new I_Piece(), new O_Piece(), new V_Piece(), new S_Piece(), new T_Piece(), new P_Piece()};

void FinishGame()
{
    game_over = true;
}

void SpawnRandomPiece()
{
    int random_piece = GetRandomValue(4, 4);
    cout << random_piece << endl;
    bool end_game = SpawnPiece(*pieces[random_piece]);

    if(end_game)
        FinishGame();
}

void UpdateMove()
{
    if(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S))
        fall_delay /= 2;
    if(IsKeyReleased(KEY_DOWN) || IsKeyReleased(KEY_S))
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

void StartGame()
{
    InitLayout();
    
    while (!WindowShouldClose())
        UpdateGame();

    CloseWindow();
}