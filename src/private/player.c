#include "player.h"

void InitPlayer(Player *player, int x, int y, int speed) {
  player->position = (Vector2){(3 * TILE_SIZE) / 2, (3 * TILE_SIZE) / 2};
  player->speed = speed;
  Image img = LoadImage(ASSETS_PATH "/player/archer.png");
  ImageResize(&img, PLAYER_SIZE, PLAYER_SIZE);
  player->texture = LoadTextureFromImage(img);
  UnloadImage(img);
}

void DrawPlayer(Player *player) {
  DrawTextureV(player->texture,
               (Vector2){player->position.x - player->texture.width / 2,
                         player->position.y - player->texture.height / 2},
               WHITE);
}

void UnloadPlayer(Player *player) { UnloadTexture(player->texture); }

void UpdatePlayer(Player *player) {

  float delta = GetFrameTime();

  Vector2 input = {0, 0};

  if (IsKeyDown(KEY_W))
    input.y -= 1;
  if (IsKeyDown(KEY_S))
    input.y += 1;
  if (IsKeyDown(KEY_A))
    input.x -= 1;
  if (IsKeyDown(KEY_D))
    input.x += 1;

  Vector2 move = Vector2Scale(Vector2Normalize(input), player->speed * delta);

  // Primero mover en X
  Vector2 moveX = {move.x, 0};
  Collision colX =
      CheckCollisionWithMap(moveX, &player->position, PLAYER_SIZE / 2);
  if (!colX.hasColided) {
    player->position.x += moveX.x;
  }

  // Luego mover en Y
  Vector2 moveY = {0, move.y};
  Collision colY =
      CheckCollisionWithMap(moveY, &player->position, PLAYER_SIZE / 2);
  if (!colY.hasColided) {
    player->position.y += moveY.y;
  }
}
