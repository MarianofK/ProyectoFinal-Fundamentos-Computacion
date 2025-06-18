#include "projectile.h"

Projectile* projectile_in_level = NULL;

void Shoot(Projectile *projectile, Player *player){

    // Calcular vector director
    Vector2 mousePos = GetMousePosition();
    Vector2 finalPos = (Vector2){(mousePos.x - player->position.x), (mousePos.y - player->position.y)};
    float module = sqrtf( finalPos.x * finalPos.x + finalPos.y * finalPos.y);

    Projectile* newProjectile = malloc(sizeof(Projectile));
    newProjectile->damage = projectile->damage;
    newProjectile->speed = projectile->speed;
    newProjectile->range = projectile->range;

    // Inicializar la direccion y posicion
    newProjectile->direction = (Vector2){finalPos.x / module, finalPos.y / module};
    newProjectile->position = (Vector2){player->position.x, player->position.y + 10};

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
            Collision collision = CheckCollisionWithMap(current->direction, &current->position, 5);
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
            if (current->range <= 0) {
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