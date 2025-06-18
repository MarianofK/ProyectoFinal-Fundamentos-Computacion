#ifndef MAP_H
#define MAP_H

#include "raylib.h"
#include "raymath.h"

#include <math.h>

#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define TILE_SIZE 70
#define PLAYER_SIZE 40

/// @brief Matriz representativa del primer mapa
static int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,0,1},
    {1,0,1,0,1,0,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,1,0,1},
    {1,1,1,1,1,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};

extern Texture2D brickWall;

/// @brief Representa la colision con el mapa
typedef struct Collision{
    Vector2 normal;
    bool hasColided;
} Collision;

/// @brief Dibuja la matriz de puntos del mapa
void DrawMap();

/// @brief Comprueba si el personaje puede seguir avanzando
/// @param direction Direccion del personaje
/// @param position Posicion del personaje
/// @param offset Desplazamiento del objeto
/// @return Retorna un TRUE si hay colision, caso contrario es FALSE
Collision CheckCollisionWithMap(Vector2 direction, Vector2 *position, float offset);

#endif