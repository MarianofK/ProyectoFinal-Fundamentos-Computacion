#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "raylib.h"
#include "raymath.h"
#include "map.h"
#include "arch.h"

#include <stdlib.h>
#include <math.h>

/// @brief Estructura del proyectil
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

/// @brief Arbol de proyectiles
extern Projectile* projectile;

/// @brief Inicializa los proyectiles
void InitProjectiles();

/// @brief Dispara un proyectile desde la posicion del jugador
/// @param playerPosition Posicion del jugador
/// @param playerDirection Direccion del jugador
void Shoot(Projectile *projectile, Vector2 playerPosition, Vector2 playerDirection, Arch arch);

/// @brief Actualiza cada proyectil en pantalla y si llegaron a su limite los elimina
void UpdateProjectile();

/// @brief Calcula la reflexion del proyectil con las colisiones
/// @param incident Vector director del proyectil
/// @param normal Vector normal de la superficie colisionada
/// @return Nueva direccion del proyectil
Vector2 Reflection(Vector2 incident, Vector2 normal);

/// @brief Limpia la lista de proyectiles en el nivel
void ClearProjectiles();

#endif