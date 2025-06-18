#include "main.h"

int main(void) {

  InitializeWindow(); // Inicializa la ventana
  InitAudioDevice();  // Funcion de raylib
  InitSettings();     // Inicializa el volumen

  GameState state = STATE_MENU;

  // Muros de ladrillo
  Image wall = LoadImage(ASSETS_PATH "/map/brickWall.png");
  ImageResize(&wall, TILE_SIZE, TILE_SIZE);
  brickWall = LoadTextureFromImage(wall);
  UnloadImage(wall);

  // Arco por defecto
  Image img = LoadImage(ASSETS_PATH "/player/arch.png");
  ImageResize(&img, PLAYER_SIZE - 10, PLAYER_SIZE - 10);
  Arch currentArch = {
      0,
      LoadTextureFromImage(img),
  };
  UnloadImage(img);

  // Proyectil por defecto
  Projectile currentProjectile = {(Vector2){0, 0}, (Vector2){0, 0}, 50.f, 400.f,
                                  500.f};

  Player player;
  InitPlayer(&player, screenWidth / 2, screenHeight / 2, 200.f);

  while (!WindowShouldClose() && state != STATE_EXIT) {
    BeginDrawing();
    ClearBackground((Color){249, 240, 240, 255});

    // Tomar el tamaño de la ventana
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    switch (state) {
    case STATE_MENU:
      DrawMenu(screenWidth / 2, screenHeight / 2);
      state = UpdateMenu();
      break;
    case STATE_GAME:
      DrawMap();
      UpdatePlayer(&player);
      DrawPlayer(&player);
      DrawArch(&currentArch, &player);
      if (IsKeyPressed(KEY_Q))
        state = STATE_MENU;
      if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        Shoot(&currentProjectile, &player);
      UpdateProjectile();
      break;
    case STATE_SETTINGS:
      DrawSettings(screenWidth / 2, screenHeight / 2);
      UpdateSettings();
      state = BackToMenu();
      if (IsKeyPressed(KEY_Q))
        state = STATE_MENU;
      break;
    default:
      break;
    }
    EndDrawing();
  }

  UnloadPlayer(&player);
  CloseWindow();
  return 0;
}
