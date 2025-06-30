#include "main.h"

int main(void) {

    InitializeWindow();
    InitAudioDevice();
    InitSettings();
    InitMap();
    InitArchs();
    InitProjectiles();

    InitAnimation();

    while (!WindowShouldClose() && state != STATE_EXIT) {
        BeginDrawing();
        ClearBackground((Color){240, 240, 240, 255});

        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();

        switch (state) {
            case STATE_MENU:
                DrawMenu(screenWidth/2, screenHeight/2);
                if(stage == STAGE_DONE){
                    UpdateMenu();
                }
                break;
            case STATE_ARCH_SELECTION:
                DrawText("Seleccion de arcos", screenWidth / 2 - 150, 10, 30, BLACK);
                switch (selection) {
                case SELECTION_PLAYER_1:
                    DrawText("Jugador 1", screenWidth / 2 - 50, screenHeight / 2 - ARCH_CARD_HEIGHT * 0.8, 30, BLACK);
                    DrawSelectionArch(screenWidth / 2, screenHeight / 2 - ARCH_CARD_HEIGHT / 2, player1.playerNumber);
                    break;
                case SELECTION_PLAYER_2:
                    DrawText("Jugador 2", screenWidth / 2 - 50, screenHeight / 2 - ARCH_CARD_HEIGHT * 0.8, 30, BLACK);
                    DrawSelectionArch(screenWidth / 2, screenHeight / 2 - ARCH_CARD_HEIGHT / 2, player2.playerNumber);
                    break;
                default:
                    break;
                }
                if (IsKeyPressed(KEY_Q)) {
                    selection = SELECTION_PLAYER_1;
                    state = STATE_MENU;
                }
                break;
            case STATE_GAME:
                if(player1.life > 0 && player2.life > 0){
                   DrawMap();
                    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_S) || IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) UpdatePlayer(&player1, 1);
                    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT)) UpdatePlayer(&player2, 2);
                    DrawPlayer(&player1);
                    DrawPlayer(&player2);
                    DrawArch(player1.currentArch, player1.position, player1.direction);
                    DrawArch(player2.currentArch, player2.position, player2.direction);
                    if (IsKeyPressed(KEY_E)) Shoot(&player1.currentProjectile, player1.position, player1.direction);
                    if (IsKeyPressed(KEY_ENTER)) Shoot(&player2.currentProjectile, player2.position, player2.direction);
                    UpdateProjectile(); 
                } else {
                    ClearProjectiles();
                    DrawEndMenu(screenWidth/2, screenHeight/2);
                    UpdateEndMenu();
                }
                if (IsKeyPressed(KEY_Q)) state = STATE_MENU;
                break;
            case STATE_ARCH_UPGRADE:
                DrawText("Actualizacion de arcos", screenWidth / 2 - 200, 10, 30, BLACK);
                switch (selection) {
                case SELECTION_PLAYER_1:
                    DrawText("Jugador 1", screenWidth / 2 - 50, screenHeight / 2 - ARCH_CARD_HEIGHT * 0.8, 30, BLACK);
                    DrawArchsToUpgrade(screenWidth / 2, screenHeight / 2 - ARCH_CARD_HEIGHT / 2, player1.playerNumber);
                    break;
                case SELECTION_PLAYER_2:
                    DrawText("Jugador 2", screenWidth / 2 - 50, screenHeight / 2 - ARCH_CARD_HEIGHT * 0.8, 30, BLACK);
                    DrawArchsToUpgrade(screenWidth / 2, screenHeight / 2 - ARCH_CARD_HEIGHT / 2, player2.playerNumber);
                    break;
                default:
                    break;
                }
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

        UpdateAnimation();

        EndDrawing();
    }
    
    UnloadPlayer(&player1);
    UnloadPlayer(&player2);
    CloseWindow();
    return 0;
}
