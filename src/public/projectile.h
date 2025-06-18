#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "raylib.h"
#include "raymath.h"
#include "player.h"
#include "map.h"

#include <stdlib.h>
#include <math.h>

/// @brief Contiene | direction(Vector2) | position(Vector2) | damage(float) | range(float) | speed(float) | previous(self) | next(self) |
typedef struct Projectile {
    Vector2 direction;
    Vector2 position;
    float damage;
    float range;
    float speed;
    struct Projectile *previous;
    struct Projectile *next;
} Projectile;

/// @brief Almacena los proyectiles activos en el mapa
extern Projectile* projectile_in_level;

/// @brief Dispara un proyectile desde la posicion del jugador
/// @param player Referencia del jugador
void Shoot(Projectile *projectile, Player *player);

/// @brief Actualiza cada proyectil en pantalla y si llegaron a su limite los elimina
void UpdateProjectile();

/// @brief Calcula la reflexion del proyectil con las colisiones
/// @param incident Vector director del proyectil
/// @param normal Vector normal de la superficie colisionada
/// @return Nueva direccion del proyectil
Vector2 Reflection(Vector2 incident, Vector2 normal);

#endif