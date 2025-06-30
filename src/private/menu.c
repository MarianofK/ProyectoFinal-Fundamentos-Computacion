#include "menu.h"
#include "definitions.h"

Rectangle btnPlay = {0, 0, rectangleWidth, rectangleHeight};
Rectangle btnOptions = {0, 0, rectangleWidth, rectangleHeight};
Rectangle btnExit = {0, 0, rectangleWidth, rectangleHeight};

Rectangle btnContinue = {0, 0, rectangleWidth, rectangleHeight};
Rectangle btnMainMenu = {0, 0, rectangleWidth, rectangleHeight};

void DrawMenu(int x, int y) {

  DrawText("The Archer", x - (rectangleWidth / 2 - 7.5), y - 130, 30, BLACK);

  btnPlay.x = x - rectangleWidth / 2;
  btnPlay.y = y - 60;
  DrawRectangleRec(btnPlay, GetButtonColor(btnPlay));
  DrawText("Empezar", btnPlay.x + (rectangleWidth / 2 - 40), btnPlay.y + 15, 20,
           BLACK);

  btnOptions.x = x - rectangleWidth / 2;
  btnOptions.y = y;
  DrawRectangleRec(btnOptions, GetButtonColor(btnOptions));
  DrawText("Ajustes", btnOptions.x + (rectangleWidth / 2 - 40),
           btnOptions.y + 15, 20, BLACK);

  btnExit.x = x - rectangleWidth / 2;
  btnExit.y = y + 60;
  DrawRectangleRec(btnExit, GetButtonColor(btnExit));
  DrawText("Salir", btnExit.x + (rectangleWidth / 2 - 25), btnExit.y + 15, 20,
           BLACK);
}

void DrawEndMenu(int x, int y) {
  DrawText(TextFormat("El jugador %d ganó", player1.life <= 0   ? 2
                                            : player2.life <= 0 ? 1
                                                                : 0),
           x - 90, y - 50, 20, BLACK);

  btnContinue.x = x - rectangleWidth / 2;
  btnContinue.y = y;
  DrawRectangleRec(btnContinue, GetButtonColor(btnContinue));
  DrawText("Continuar", btnContinue.x + (rectangleWidth / 2 - 50),
           btnContinue.y + 15, 20, BLACK);

  btnMainMenu.x = x - rectangleWidth / 2;
  btnMainMenu.y = y + 60;
  DrawRectangleRec(btnMainMenu, GetButtonColor(btnMainMenu));
  DrawText("Menu", btnMainMenu.x + (rectangleWidth / 2 - 30),
           btnMainMenu.y + 15, 20, BLACK);
}

void UpdateMenu() {
  Vector2 mouse = GetMousePosition();
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    if (CheckCollisionPointRec(mouse, btnPlay)) {
      InitPlayer(&player1, (3 * TILE_SIZE) / 2, (3 * TILE_SIZE) / 2, 200.f, 1);
      InitPlayer(&player2, TILE_SIZE * (MAP_WIDTH - 1.5),
                 TILE_SIZE * (MAP_HEIGHT - 1.5), 200.f, 2);
      state = STATE_MINI_GAME;
      return;
    }
    if (CheckCollisionPointRec(mouse, btnOptions)) {
      state = STATE_SETTINGS;
      return;
    }
    if (CheckCollisionPointRec(mouse, btnExit)) {
      state = STATE_EXIT;
      return;
    }
  }
}

void UpdateEndMenu() {
  Vector2 mouse = GetMousePosition();
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    if (CheckCollisionPointRec(mouse, btnContinue)) {
      InitPlayer(&player1, (3 * TILE_SIZE) / 2, (3 * TILE_SIZE) / 2, 200.f, 1);
      InitPlayer(&player2, TILE_SIZE * (MAP_WIDTH - 1.5),
                 TILE_SIZE * (MAP_HEIGHT - 1.5), 200.f, 2);
      state = STATE_MINI_GAME;
      return;
    }
    if (CheckCollisionPointRec(mouse, btnMainMenu)) {
      state = STATE_MENU;
      return;
    }
  }
}
