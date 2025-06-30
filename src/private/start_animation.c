#include "start_animation.h"

AnimationStage stage = STAGE_MOVE_CENTER;

void InitAnimation() {
    position = (Vector2){ GetScreenWidth() / 2 -25, GetScreenHeight() / 2 - 25 };
    target = (Vector2){ GetScreenWidth() / 2, GetScreenHeight() / 2};
    size = (Vector2){ 50, 50 };
    rotation = 0;
    alpha = 1.f;
    time = 2.f;
}

void UpdateAnimation() {

    if (stage == STAGE_DONE) return;

    float scaleSpeed = 35.0f;

    switch (stage) {
        case STAGE_MOVE_CENTER:
            time -= 0.1;
            if(time <= 0.f){
                stage = STAGE_SCALE;
            }
            break;

        case STAGE_SCALE:
            size.y += scaleSpeed;
            if (size.y >= screenHeight) {
                stage = STAGE_EXPAND_FULLSCREEN;
            }
            break;

        case STAGE_EXPAND_FULLSCREEN:
            size.x += scaleSpeed;
            size.y += scaleSpeed;
            position.x = screenWidth / 2;
            position.y = screenHeight / 2;
            if (size.x >= screenWidth && size.y >= screenHeight) {
                size.x = screenWidth;
                size.y = screenHeight;
                stage = STAGE_FADEOUT;
            }
            break;

        case STAGE_FADEOUT:
            alpha -= 0.02;
            if (alpha <= 0.0f) {
                alpha = 0.0f;
                stage = STAGE_DONE;
            }
            break;

        case STAGE_DONE:
            break;
    }

    Color color = (Color){ 0, 0, 0, (alpha * 255) };
    DrawRectangle(0, 0, screenWidth, screenHeight, (Color){240, 240, 240, (alpha * 255)});
    DrawRectanglePro(
        (Rectangle){ position.x, position.y, size.x, size.y },
        (Vector2){ size.x / 2, size.y / 2 },
        rotation,
        color
    );
}