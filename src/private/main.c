#include "main.h"

int main(void) {

    InitializeWindow();
    InitAudioDevice();
    InitSettings();
    InitMap();
    InitArchs();
    InitProjectiles();

    while (!WindowShouldClose() && state != STATE_EXIT) {
        BeginDrawing();
        ClearBackground((Color){240, 240, 240, 255});

        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();

        switch (state) {
            case STATE_MENU:
                DrawMenu(screenWidth/2, screenHeight/2);
                UpdateMenu();
                break;
            case STATE_GAME:
                if(player1.life > 0 && player2.life > 0){
                   DrawMap();
                    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_S) || IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) UpdatePlayer(&player1, 1);
                    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT)) UpdatePlayer(&player2, 2);
                    DrawPlayer(&player1);
                    DrawPlayer(&player2);
                    DrawArch(&player1.currentArch, player1.position, player1.direction);
                    DrawArch(&player2.currentArch, player2.position, player2.direction);
                    if (IsKeyPressed(KEY_E)) Shoot(&player1.currentProjectile, player1.position, player1.direction);
                    if (IsKeyPressed(KEY_ENTER)) Shoot(&player2.currentProjectile, player2.position, player2.direction);
                    UpdateProjectile(); 
                } else {
                    DrawEndMenu(screenWidth/2, screenHeight/2);
                    UpdateEndMenu();
                }
                if (IsKeyPressed(KEY_Q)) state = STATE_MENU;
                break;

            case STATE_SETTINGS:
                DrawSettings(screenWidth/2, screenHeight/2);
                UpdateSettings();
                BackToMenu();
                if (IsKeyPressed(KEY_Q)) state = STATE_MENU;
                break;
            default:
                break;
        }
        EndDrawing();
    }
    
    UnloadPlayer(&player1);
    UnloadPlayer(&player2);
    CloseWindow();
    return 0;
}
