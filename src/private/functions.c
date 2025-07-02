#include "functions.h"
#include "definitions.h"
#include "stdlib.h"

void InitializeWindow(){
    screenHeight = initialHeight;
    screenWidth = initialWidth;
    InitWindow(initialWidth, initialHeight, "Battlearcher");
    SetTargetFPS(60);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
};

void PlayLevelMusic(const char *path) {
    if (gameMusic.stream.buffer != NULL)
    {
        StopMusicStream(gameMusic);
        UnloadMusicStream(gameMusic);
    }
    gameMusic = LoadMusicStream(path);
    PlayMusicStream(gameMusic);
}

void DrawTextCentered(const char *text, int x, int y, int fontSize, Color color) {
    int textWidth = MeasureText(text, fontSize);
    int textHeight = fontSize;
    DrawText(text, x - textWidth / 2, y - textHeight / 2, fontSize, color);
}

void DrawTextureCentered(Texture2D texture, int centerX, int centerY, Color tint) {
    int texWidth = texture.width;
    int texHeight = texture.height;

    DrawTexture(texture, centerX - texWidth / 2, centerY - texHeight / 2, tint);
}

bool DrawButton(char *text, Texture2D normal, Texture2D hover, Rectangle bounds, Color color) {
    Vector2 mouse = GetMousePosition();
    bool hovered = CheckCollisionPointRec(mouse, bounds);
    DrawTexture(hovered ? hover : normal, bounds.x, bounds.y, WHITE);
    DrawTextCentered(text, bounds.x + bounds.width/2, bounds.y + bounds.height / 2, 20, color);
    return hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

bool DrawCard(Texture2D normal, Rectangle bounds) {
    Vector2 mouse = GetMousePosition();
    DrawTexture(normal, bounds.x, bounds.y, WHITE);
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}