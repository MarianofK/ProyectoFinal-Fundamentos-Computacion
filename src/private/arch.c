#include "arch.h"

Arch *archs = NULL;

void InitArchs(){

    Image img = LoadImage(ASSETS_PATH "/player/arch.png");
    ImageResize(&img, PLAYER_SIZE - 10, PLAYER_SIZE - 10);
    Arch *initial = malloc(sizeof(Arch));
    *initial = (Arch){
        0,
        LoadTextureFromImage(img),
    };
    UnloadImage(img);
    archs = initial;
}

void DrawArch(Arch *arch, Vector2 playerPosition, Vector2 playerDirection){

    // Calcular ángulo en radianes, luego convertir a grados
    float angle = atan2f(playerDirection.y, playerDirection.x) * RAD2DEG;

    DrawTexturePro(
        arch->texture, 
        (Rectangle){0, 0, arch->texture.width, arch->texture.height},
        (Rectangle){playerPosition.x, playerPosition.y + 10, arch->texture.width, arch->texture.height},
        (Vector2){arch->texture.width / 2, arch->texture.height / 2},
        angle,
        WHITE
    );
}