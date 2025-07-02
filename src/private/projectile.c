#include "projectile.h"

Projectile *projectile_in_level = NULL;

Projectile *projectile = NULL;

void InitProjectiles(){
    
    Projectile *initial = malloc(sizeof(Projectile));

    *initial = (Projectile) {
        (Vector2){ 0, 0 },
        (Vector2){ 0, 0 },
        0.f,
        0.f,
        0.f
    };

    projectile = initial;
}

void Shoot(Projectile *projectile, Vector2 playerPosition, Vector2 playerDirection, Arch arch){

    Projectile* newProjectile = malloc(sizeof(Projectile));

    // Inicializar la direccion y posicion
    newProjectile->direction = playerDirection;
    newProjectile->position = (Vector2){playerPosition.x + (playerDirection.x * (PLAYER_SIZE * 0.7)), playerPosition.y + (playerDirection.y * (PLAYER_SIZE * 0.7))};

    // Otros datos del proyectil
    newProjectile->damage = arch.damage;
    newProjectile->range = arch.range;
    newProjectile->speed = arch.speed;

    // Apilar el nuevo proyectil
    newProjectile->next = projectile_in_level;
    projectile_in_level = newProjectile;
}

void UpdateProjectile(){
    if(projectile_in_level != NULL){

        float delta = GetFrameTime(), dx = 0, dy = 0, module = 0;

        Projectile* current = projectile_in_level;
        Projectile* aux = NULL;
        Projectile* toDelete = NULL;

        while (current != NULL){
            Collision collision = CheckCollisionWithMap(current->direction, &current->position, 1, true, current->damage);
            if(collision.hasColided){
                current->direction = Reflection(current->direction, collision.normal);
            }
            dx = current->direction.x * current->speed * delta;
            dy = current->direction.y * current->speed * delta;
            module = sqrtf(dx * dx + dy * dy);
            toDelete = NULL;
            current->position.x += dx;
            current->position.y += dy;
            current->range -= module;
            if (current->range <= 0 || collision.withPlayer) {
                toDelete = current;
                current = current->next;
                if (aux == NULL) {
                    projectile_in_level = current;
                } else {
                    aux->next = current;
                }
                free(toDelete);
                continue;
            }
            DrawCircleV(current->position, 5, RED);
            aux = current;
            current = current->next;
        }
    }
}

Vector2 Reflection(Vector2 incident, Vector2 normal){
    float dotProduct = (incident.x * normal.x) + (incident.y * normal.y);
    // Reflexion de un vector -> R = I - (2 * N * (N . I))
    return (Vector2){incident.x - (2 * normal.x * dotProduct), incident.y - (2 * normal.y * dotProduct)};
}

void ClearProjectiles(){
    Projectile* aux = NULL; 
    while (projectile_in_level != NULL){
        aux = projectile_in_level;
        projectile_in_level = projectile_in_level->next;
        free(aux);
    }
    projectile_in_level = NULL;
}