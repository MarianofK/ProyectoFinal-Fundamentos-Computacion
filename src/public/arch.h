#ifndef ARCH_H
#define ARCH_H

#define ARCH_CARD_HEIGHT 200
#define ARCH_CARD_WIDTH 150

#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include "map.h"
#include "definitions.h"

#include <math.h>

/// @brief Contiene | cadence(float) | texture(Texture2D) | previous(izquierda) | next(derecha) |
typedef struct Arch {
    char *name;
    float cadence;
    int cost;
    Texture2D texture;
    struct Arch *previous;
    struct Arch *next;
} Arch;

/// @brief Arbol de arcos
extern Arch *arch1, *arch2, *arch3;

/// @brief Inicializar los arcos
void InitArchs();

/// @brief Dibuja el arco orientado hacia el puntero
/// @param playerPosition Posicion del jugador
/// @param playerDirection Direccion a la que mira el jugador
void DrawArch(Arch *arch, Vector2 playerPosition, Vector2 playerDirection);

/// @brief Dibuja la seleccion inicial de los arcos
/// @param x Posicion de dibujo en X
/// @param y Posicion de dibujo en Y
/// @param playerNumber Numero del jugador
void DrawSelectionArch(int x, int y, int playerNumber);

/// @brief Dibuja siguientes arcos del arbol para actualizarlos
/// @param x Posicion de dibujo en X
/// @param y Posicion de dibujo en Y
/// @param playerNumber Numero del jugador
void DrawArchsToUpgrade(int x, int y, int playerNumber);

#endif