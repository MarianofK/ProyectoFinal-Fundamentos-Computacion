#include "main.h"
#include "definitions.h"

extern int mini_game(void);

GameState old_state = STATE_EXIT;

int main(void)
{
  InitializeWindow();
  InitAudioDevice();

  InitMenu();
  InitSettings();
  InitMap();
  InitArchs();
  InitProjectiles();

  InitAnimation();

  while (!WindowShouldClose() && state != STATE_EXIT)
  {
    BeginDrawing();
    UpdateMusicStream(gameMusic);
    ClearBackground((Color){240, 240, 240, 255});

    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    if(old_state != state){
      old_state = state;
      switch (state)
      {
      case STATE_MENU:
        PlayLevelMusic(ASSETS_PATH "/sounds/menu.wav");
        break;
      case STATE_MINI_GAME:
        PlayLevelMusic(ASSETS_PATH "/sounds/nivel_1.wav");
        break;
      case STATE_GAME:
        PlayLevelMusic(ASSETS_PATH "/sounds/nivel_2.wav");
        break;
      default:
        break;
      }
    }

    switch (state)
    {
    case STATE_MENU:
      DrawMenu(screenWidth / 2, screenHeight / 2);
      break;
    case STATE_MINI_GAME:
      mini_game();
    case STATE_ARCH_SELECTION:
      DrawTextCentered("Seleccion de arcos", screenWidth / 2, 10, 30, WHITE);
      switch (selection)
      {
      case SELECTION_PLAYER_1:
        DrawTextCentered("Jugador 1", screenWidth / 2, screenHeight / 2 - ARCH_CARD_HEIGHT * 0.8, 20, WHITE);
        DrawSelectionArch(screenWidth / 2, screenHeight / 2 - ARCH_CARD_HEIGHT / 2, player1.playerNumber);
        break;
      case SELECTION_PLAYER_2:
        DrawTextCentered("Jugador 2", screenWidth / 2, screenHeight / 2 - ARCH_CARD_HEIGHT * 0.8, 20, WHITE);
        DrawSelectionArch(screenWidth / 2, screenHeight / 2 - ARCH_CARD_HEIGHT / 2, player2.playerNumber);
        break;
      default:
        break;
      }
      if (IsKeyPressed(KEY_Q))
      {
        selection = SELECTION_PLAYER_1;
        state = STATE_MENU;
      }
      break;
    case STATE_GAME:
      if (player1.life > 0 && player2.life > 0)
      {
        if (player1.currentArch != NULL && &player1.currentProjectile != NULL)
        {
          player1.currentProjectile.damage = player1.currentArch->damage;
          player1.currentProjectile.range = player1.currentArch->range;
        }
        if (player2.currentArch != NULL && &player2.currentProjectile != NULL)
        {
          player2.currentProjectile.damage = player2.currentArch->damage;
          player2.currentProjectile.range = player2.currentArch->range;
        }
        DrawMap();
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_S) || IsKeyDown(KEY_A) ||
            IsKeyDown(KEY_D))
          UpdatePlayer(&player1, 1);
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT))
          UpdatePlayer(&player2, 2);
        DrawPlayer(&player1);
        DrawPlayer(&player2);
        DrawArch(player1.currentArch, player1.position, player1.direction);
        DrawArch(player2.currentArch, player2.position, player2.direction);
        if (IsKeyPressed(KEY_E))
          Shoot(&player1.currentProjectile, player1.position, player1.direction, *player1.currentArch);
        if (IsKeyPressed(KEY_ENTER))
          Shoot(&player2.currentProjectile, player2.position, player2.direction, *player2.currentArch);
        UpdateProjectile();
      }
      else
      {
        ClearProjectiles();
        DrawEndMenu(screenWidth / 2, screenHeight / 2);
      }
      if (IsKeyPressed(KEY_Q))
        state = STATE_MENU;
      break;
    case STATE_ARCH_UPGRADE:
      DrawTextCentered("Actualizacion de arcos", screenWidth / 2, 10, 30, WHITE);
      switch (selection)
      {
      case SELECTION_PLAYER_1:
        DrawTextCentered("Jugador 1", screenWidth / 2, screenHeight / 2 - ARCH_CARD_HEIGHT * 0.8, 30, WHITE);
        DrawArchsToUpgrade(screenWidth / 2, screenHeight / 2 - ARCH_CARD_HEIGHT / 2, player1.playerNumber);
        break;
      case SELECTION_PLAYER_2:
        DrawTextCentered("Jugador 2", screenWidth / 2, screenHeight / 2 - ARCH_CARD_HEIGHT * 0.8, 30, WHITE);
        DrawArchsToUpgrade(screenWidth / 2, screenHeight / 2 - ARCH_CARD_HEIGHT / 2, player2.playerNumber);
        break;
      default:
        break;
      }
      break;
    case STATE_SETTINGS:
      DrawSettings(screenWidth / 2, screenHeight / 2);
      UpdateSettings();
      if (IsKeyPressed(KEY_Q))
        state = STATE_MENU;
      break;
    default:
      break;
    }

    UpdateAnimation();

    EndDrawing();
  }
  EndDrawing();
  UnloadPlayer(&player1);
  UnloadPlayer(&player2);
  FreeArchTree(arch1);
  FreeArchTree(arch2);
  FreeArchTree(arch3);
  UnloadMusicStream(gameMusic);
  CloseAudioDevice();
  CloseWindow();

  return 0;
}
