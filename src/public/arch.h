#ifndef ARCH_H
#define ARCH_H

#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include "map.h"

#include <math.h>

/// @brief Contiene | cadence(float) | texture(Texture2D) | previous(self) | next(self) |
typedef struct Arch {
    float cadence;
    Texture2D texture;
    struct Arch *previous;
    struct Arch *next;
} Arch;

/// @brief Arbol de arcos
extern Arch *archs;

/// @brief Inicializar los arcos
void InitArchs();

/// @brief Dibuja el arco orientado hacia el puntero
/// @param playerPosition Posicion del jugador
/// @param playerDirection Direccion a la que mira el jugador
void DrawArch(Arch *arch, Vector2 playerPosition, Vector2 playerDirection);

#endif