#include "main_menu.h"

Rectangle main_menu_btnPlay = {0, 0, rectangleWidth, rectangleHeight};
Rectangle main_menu_btnOptions = {0, 0, rectangleWidth, rectangleHeight};
Rectangle main_menu_btnExit = {0, 0, rectangleWidth, rectangleHeight};

void DrawMainMenu(int x, int y) {

  DrawText("The Archer", x - (rectangleWidth / 2 - 7.5), y - 130, 30, BLACK);

  main_menu_btnPlay.x = x - rectangleWidth / 2;
  main_menu_btnPlay.y = y - 60;
  DrawRectangleRec(main_menu_btnPlay, GetButtonColor(main_menu_btnPlay));
  DrawText("Empezar", main_menu_btnPlay.x + (rectangleWidth / 2 - 40),
           main_menu_btnPlay.y + 15, 20, BLACK);

  main_menu_btnOptions.x = x - rectangleWidth / 2;
  main_menu_btnOptions.y = y;
  DrawRectangleRec(main_menu_btnOptions, GetButtonColor(main_menu_btnOptions));
  DrawText("Ajustes", main_menu_btnOptions.x + (rectangleWidth / 2 - 40),
           main_menu_btnOptions.y + 15, 20, BLACK);

  main_menu_btnExit.x = x - rectangleWidth / 2;
  main_menu_btnExit.y = y + 60;
  DrawRectangleRec(main_menu_btnExit, GetButtonColor(main_menu_btnExit));
  DrawText("Salir", main_menu_btnExit.x + (rectangleWidth / 2 - 25),
           main_menu_btnExit.y + 15, 20, BLACK);
}

GameState UpdateMainMenu() {
  Vector2 mouse = GetMousePosition();
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    if (CheckCollisionPointRec(mouse, main_menu_btnPlay)) {
      return STATE_GAME;
    } else if (CheckCollisionPointRec(mouse, main_menu_btnOptions)) {
      return STATE_SETTINGS;
    } else if (CheckCollisionPointRec(mouse, main_menu_btnExit)) {
      return STATE_EXIT;
    }
  }
  return STATE_MENU;
}
