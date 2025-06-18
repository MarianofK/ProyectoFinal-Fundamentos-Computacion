#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "map.h"

#include <stdio.h>
#include <math.h>

/// @brief Contiene | position (Vector2) | speed (float) | texture (Texture2D) |
typedef struct Player {
    Vector2 position;
    float speed;
    Texture2D texture;
} Player;

/// @brief Inicializa el personaje estableciendo su posicion, velocidad y textura
/// @param player Puntero al personaje
void InitPlayer(Player* player, int x, int y, int speed);

/// @brief Dibuja al personaje en el nivel
/// @param player Puntero al personaje
void DrawPlayer(Player* player);

/// @brief Elimina la textura del personaje
/// @param player Puntero al personaje
void UnloadPlayer(Player* player);

/// @brief Comprueba si se pulso alguna tecla de movimiento y actualiza su posicion
/// @param player Puntero al personaje
void UpdatePlayer(Player* player);

#endif