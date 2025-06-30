#ifndef START_ANIMATION_H
#define START_ANIMATION_H

#include "raylib.h"
#include "definitions.h"

typedef enum {
    STAGE_MOVE_CENTER,
    STAGE_SCALE,
    STAGE_EXPAND_FULLSCREEN,
    STAGE_FADEOUT,
    STAGE_DONE
} AnimationStage;

static Vector2 position = { 0 };
static Vector2 target = { 0 };
static Vector2 size = { 0 };
static float rotation = 0;
extern AnimationStage stage;
static float alpha;
static float time;

void InitAnimation();
void UpdateAnimation();

#endif