#include "menu.h"

Rectangle menu_btnPlay = {0, 0, rectangleWidth, rectangleHeight};
Rectangle menu_btnOptions = {0, 0, rectangleWidth, rectangleHeight};
Rectangle menu_btnExit = {0, 0, rectangleWidth, rectangleHeight};

Rectangle btnContinue = {0, 0, rectangleWidth, rectangleHeight};
Rectangle btnMenu = {0, 0, rectangleWidth, rectangleHeight};

void DrawMenu(int x, int y) {

  DrawText("The Archer", x - (rectangleWidth / 2 - 7.5), y - 130, 30, BLACK);

  menu_btnPlay.x = x - rectangleWidth / 2;
  menu_btnPlay.y = y - 60;
  DrawRectangleRec(menu_btnPlay, GetButtonColor(menu_btnPlay));
  DrawText("Empezar", menu_btnPlay.x + (rectangleWidth / 2 - 40),
           menu_btnPlay.y + 15, 20, BLACK);

  menu_btnOptions.x = x - rectangleWidth / 2;
  menu_btnOptions.y = y;
  DrawRectangleRec(menu_btnOptions, GetButtonColor(menu_btnOptions));
  DrawText("Ajustes", menu_btnOptions.x + (rectangleWidth / 2 - 40),
           menu_btnOptions.y + 15, 20, BLACK);

  menu_btnExit.x = x - rectangleWidth / 2;
  menu_btnExit.y = y + 60;
  DrawRectangleRec(menu_btnExit, GetButtonColor(menu_btnExit));
  DrawText("Salir", menu_btnExit.x + (rectangleWidth / 2 - 25),
           menu_btnExit.y + 15, 20, BLACK);
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

  btnMenu.x = x - rectangleWidth / 2;
  btnMenu.y = y + 60;
  DrawRectangleRec(btnMenu, GetButtonColor(btnMenu));
  DrawText("Menu", btnMenu.x + (rectangleWidth / 2 - 30), btnMenu.y + 15, 20,
           BLACK);
}

void UpdateMenu() {
  Vector2 mouse = GetMousePosition();
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    if (CheckCollisionPointRec(mouse, menu_btnPlay)) {
      InitPlayer(&player1, (3 * TILE_SIZE) / 2, (3 * TILE_SIZE) / 2, 200.f, 1);
      InitPlayer(&player2, TILE_SIZE * (MAP_WIDTH - 1.5),
                 TILE_SIZE * (MAP_HEIGHT - 1.5), 200.f, 2);
      state = STATE_GAME;
      return;
    }
    if (CheckCollisionPointRec(mouse, menu_btnOptions)) {
      state = STATE_SETTINGS;
      return;
    }
    if (CheckCollisionPointRec(mouse, menu_btnExit)) {
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
      state = STATE_GAME;
      return;
    }
    if (CheckCollisionPointRec(mouse, btnMenu)) {
      state = STATE_MENU;
      return;
    }
  }
}
