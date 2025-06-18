#ifndef ARCH_H
#define ARCH_H

#include "raylib.h"
#include "player.h"

/// @brief Contiene | cadence(float) | texture(Texture2D) | previous(self) | next(self) |
typedef struct Arch {
    float cadence;
    Texture2D texture;
    struct Arch *previous;
    struct Arch *next;
} Arch;

/// @brief Dibuja el arco orientado hacia el puntero
/// @param player Referencia del jugador
void DrawArch(Arch *arch, Player *player);

#endif