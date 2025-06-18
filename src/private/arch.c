#include "arch.h"

void DrawArch(Arch *arch, Player *player) {

  Vector2 mouse = GetMousePosition();

  // Calcular ángulo en radianes, luego convertir a grados
  float angle =
      atan2f(mouse.y - player->position.y, mouse.x - player->position.x) *
      RAD2DEG;

  DrawTexturePro(arch->texture,
                 (Rectangle){0, 0, arch->texture.width, arch->texture.height},
                 (Rectangle){player->position.x, player->position.y + 10,
                             arch->texture.width, arch->texture.height},
                 (Vector2){arch->texture.width / 2, arch->texture.height / 2},
                 angle, WHITE);
}
