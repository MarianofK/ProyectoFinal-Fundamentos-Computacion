#include "settings.h"
#include "menu.h"

Rectangle volumeBar = { 0, 0, rectangleWidth, 10 };
float volume = 0.5f;

void InitSettings() {
    SetMasterVolume(volume);
}

void DrawSettings(int x, int y) {

    DrawTexturePro(
        background,
        (Rectangle){0, 0, (float)background.width, (float)background.height},
        (Rectangle){0, 0, (float)screenWidth, (float)screenHeight},
        (Vector2){0, 0},
        0.0f,
        WHITE
    );

    volumeBar.x = x - 40;
    volumeBar.y = y - 40;

    DrawTextCentered("Ajustes", x, volumeBar.y - 60, 30, WHITE);
    DrawTextCentered("Volumen", x - 100, volumeBar.y + 10, 20, WHITE);

    // Rectangulo
    DrawRectangleRec(volumeBar, DARKGRAY);

    // Barra de progreso
    DrawRectangle(volumeBar.x, volumeBar.y, volume * rectangleWidth, volumeBar.height, GRAY);

    // Indicador
    DrawCircle(volumeBar.x + volume * rectangleWidth, volumeBar.y + volumeBar.height / 2, 10, BLACK);

    if(DrawButton("Volver", btnImage, btnImageHover, (Rectangle){x - rectangleWidth / 2, y + 10, rectangleWidth, rectangleHeight}, WHITE)){
        state = STATE_MENU;
    }
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