#include "main_menu.h"


Rectangle btnPlay    = { 0, 0, rectangleWidth, rectangleHeight };
Rectangle btnOptions = { 0, 0, rectangleWidth, rectangleHeight };
Rectangle btnExit    = { 0, 0, rectangleWidth, rectangleHeight };

void DrawMenu(int x, int y) {

    DrawText("The Archer", x - (rectangleWidth/2 - 7.5), y - 130, 30, BLACK);

    btnPlay.x = x - rectangleWidth/2;
    btnPlay.y = y - 60;
    DrawRectangleRec(btnPlay, GetButtonColor(btnPlay));
    DrawText("Empezar", btnPlay.x + (rectangleWidth/2 - 40), btnPlay.y + 15, 20, BLACK);

    btnOptions.x = x - rectangleWidth/2;
    btnOptions.y = y;
    DrawRectangleRec(btnOptions, GetButtonColor(btnOptions));
    DrawText("Ajustes", btnOptions.x + (rectangleWidth/2 - 40), btnOptions.y + 15, 20, BLACK);

    btnExit.x = x - rectangleWidth/2;
    btnExit.y = y + 60;
    DrawRectangleRec(btnExit, GetButtonColor(btnExit));
    DrawText("Salir", btnExit.x + (rectangleWidth/2 - 25), btnExit.y + 15, 20, BLACK);
}

GameState UpdateMenu() {
    Vector2 mouse = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mouse, btnPlay)) {
            return STATE_GAME;
        } else if (CheckCollisionPointRec(mouse, btnOptions)) {
            return STATE_SETTINGS;
        } else if (CheckCollisionPointRec(mouse, btnExit)) {
            return STATE_EXIT;
        }
    }
    return STATE_MENU;
}
