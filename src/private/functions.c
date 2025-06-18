#include "functions.h"
#include "definitions.h"

void InitializeWindow(){
    screenHeight = initialHeight;
    screenWidth = initialWidth;
    InitWindow(initialWidth, initialHeight, "The Archer");
    SetTargetFPS(60);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
};

Color GetButtonColor(Rectangle rect) {
    return CheckCollisionPointRec(GetMousePosition(), rect) ? GRAY : LIGHTGRAY;
}