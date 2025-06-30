#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "map.h"
#include "projectile.h"
#include "arch.h"

#include <stdio.h>
#include <math.h>

/// @brief Estructura del jugador
typedef struct Player {
    float life;
    float speed;
    int playerNumber;
    Vector2 position;
    Vector2 direction;
    Texture2D texture;
    Projectile currentProjectile;
    Arch *currentArch;
} Player;

/// @brief Jugador 1
extern Player player1;

/// @brief Jugador 2
extern Player player2;

/// @brief Inicializa el personaje estableciendo su posicion, velocidad y textura
/// @param player Puntero al personaje
/// @param x Posicion de inicio en X
/// @param y Posicion de inicio en Y
/// @param speed Velocidad constante
/// @param playerNumber Numero del jugador
void InitPlayer(Player* player, float x, float y, float speed, int playerNumber);

/// @brief Dibuja al personaje en el nivel
/// @param player Puntero al personaje
void DrawPlayer(Player* player);

/// @brief Elimina la textura del personaje
/// @param player Puntero al personaje
void UnloadPlayer(Player* player);

/// @brief Comprueba si se pulso alguna tecla de movimiento y actualiza su posicion
/// @param player Puntero al personaje
/// @param playerNumber Numero del jugador que se mueve
void UpdatePlayer(Player* player, int playerNumber);

#endif