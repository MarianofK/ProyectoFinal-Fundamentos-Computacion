#include "settings.h"

Rectangle volumeBar = { 0, 0, rectangleWidth, 10 };
Rectangle backButton = { 0, 0, rectangleWidth, rectangleHeight};
float volume = 0.5f;

void InitSettings() {
    SetMasterVolume(volume);
}

void DrawSettings(int x, int y) {

    volumeBar.x = x - 10;
    volumeBar.y = y - 20;

    DrawText("Ajustes", x - 60, volumeBar.y - 60, 30, BLACK);
    DrawText("Volumen", x - 130, volumeBar.y - 5, 20, BLACK);

    // Rectangulo
    DrawRectangleRec(volumeBar, DARKGRAY);

    // Barra de progreso
    DrawRectangle(volumeBar.x, volumeBar.y, volume * rectangleWidth, volumeBar.height, GRAY);

    // Indicador
    DrawCircle(volumeBar.x + volume * rectangleWidth, volumeBar.y + volumeBar.height / 2, 10, BLACK);

    // Boton para volver
    backButton.x = x - backButton.width/2;
    backButton.y = y + 10;
    DrawRectangleRec(backButton, GetButtonColor(backButton));
    DrawText("Volver", backButton.x + 65, backButton.y + 15, 20, BLACK);
}

void UpdateSettings() {
    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, volumeBar)) {
        volume = (mouse.x - volumeBar.x) / rectangleWidth;

        if (volume < 0.0f) volume = 0.0f;
        if (volume > 1.0f) volume = 1.0f;

        SetMasterVolume(volume);
    }
}

float GetVolume() {
    return volume;
}

void BackToMenu() {
    Vector2 mouse = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mouse, backButton)) {
            state = STATE_MENU;
        }
    }
}