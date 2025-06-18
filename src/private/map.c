#include "map.h"

Texture2D brickWall = {0};

void DrawMap() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map[y][x] == 1 ? DrawTextureV(brickWall, (Vector2){ x * TILE_SIZE, y * TILE_SIZE }, WHITE) : DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, LIGHTGRAY);
        }
    }
}

Collision CheckCollisionWithMap(Vector2 direction, Vector2 *position, float offset) {
    Collision result = {0};
    result.hasColided = false;
    result.normal = (Vector2){0, 0};

    // Proyectar movimiento
    Vector2 nextPos = Vector2Add(*position, Vector2Scale(direction, offset / 8));
    Rectangle nextRect = {
        nextPos.x - offset,
        nextPos.y - offset,
        offset * 2,
        offset * 2
    };

    // Buscar qué celdas del mapa toca
    int minX = (int)floorf(nextRect.x / TILE_SIZE);
    int minY = (int)floorf(nextRect.y / TILE_SIZE);
    int maxX = (int)floorf((nextRect.x + nextRect.width) / TILE_SIZE);
    int maxY = (int)floorf((nextRect.y + nextRect.height) / TILE_SIZE);

    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT) continue;

            if (map[y][x] != 0) {
                
                // Rectángulo del tile sólido
                Rectangle tileRect = {
                    x * TILE_SIZE,
                    y * TILE_SIZE,
                    TILE_SIZE,
                    TILE_SIZE
                };

                if (CheckCollisionRecs(nextRect, tileRect)) {
                    result.hasColided = true;

                    // Determinar normal según la direccion del proyectil
                    Vector2 tileCenter = {
                        tileRect.x + tileRect.width / 2.0f,
                        tileRect.y + tileRect.height / 2.0f
                    };

                    Vector2 diff = Vector2Subtract(*position, tileCenter);
                    if (fabsf(diff.x) > fabsf(diff.y)) {
                        result.normal = (Vector2){diff.x > 0 ? 1 : -1, 0};
                    } else {
                        result.normal = (Vector2){0, diff.y > 0 ? 1 : -1};
                    }

                    // Corregir la posición del objetivo
                    if (result.normal.x != 0){
                        position->x = result.normal.x > 0 ? (tileRect.x + tileRect.width + offset) : (tileRect.x - offset);
                    } else {
                        position->y = result.normal.y > 0 ? (tileRect.y + tileRect.height + offset) : (tileRect.y - offset);
                    }

                    return result;
                }
            }
        }
    }

    return result;
}
