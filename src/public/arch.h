#ifndef ARCH_H
#define ARCH_H

#define MAX_ARCHES 128
#define MAX_LINE_LENGTH 256
#define ARCH_CARD_HEIGHT 300
#define ARCH_CARD_WIDTH 300

#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"
#include "map.h"
#include "definitions.h"

#include <math.h>

/// @brief Estructura del arcos
typedef struct Arch {
    int index;
    char *name;
    float range;
    int damage;
    float speed;
    int cost;
    Texture2D texture;
    Texture2D arch;
    struct Arch *previous;
    struct Arch *next;
} Arch;


/// @brief Imagen de las cartas
extern Texture2D cardImage;
extern Texture2D cardImageBloqued;

/// @brief Arbol de arcos
extern Arch *arch1, *arch2, *arch3;

/// @brief Control de seleccion de arcos
extern bool bSelected;

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

Arch *InsertArchNodeInOrder(Arch *root, Arch *newNode);

Arch *LoadArchTreeFromCSV(const char *filename);

void FreeArchTree(Arch *root);

#endif