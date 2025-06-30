#include "player.h"
#include "definitions.h"

Player player1 = {0};
Player player2 = {0};

void InitPlayer(Player *player, float x, float y, float speed,
                int playerNumber) {

  player->life = 100;
  player->speed = speed;
  player->playerNumber = playerNumber;

  player->position = (Vector2){x, y};
  player->direction = (Vector2){1, 0};

  Image img = LoadImage(ASSETS_PATH "/player/archer.png");
  ImageResize(&img, PLAYER_SIZE, PLAYER_SIZE);
  player->texture = LoadTextureFromImage(img);
  UnloadImage(img);

  player->currentArch = NULL;
  player->currentProjectile = *projectiles;
}

void DrawPlayer(Player *player) {
  DrawTextureV(player->texture,
               (Vector2){player->position.x - player->texture.width / 2,
                         player->position.y - player->texture.height / 2},
               WHITE);
  DrawText(TextFormat("Player 1: %.1f", player1.life), 900, 30, 20, BLACK);
  DrawText(TextFormat("Score Player 1: %i", score_player1), 900, 60, 20, BLACK);
  DrawText(TextFormat("Player 2: %.1f", player2.life), 900, 90, 20, BLACK);
  DrawText(TextFormat("Score Player 2: %i", score_player2), 900, 120, 20,
           BLACK);
}

void UnloadPlayer(Player *player) { UnloadTexture(player->texture); }

void UpdatePlayer(Player *player, int playerNumber) {

  float delta = GetFrameTime();

  Vector2 input = {0, 0};

  switch (playerNumber) {
  case 1:
    // Controles del primer jugador
    if (IsKeyDown(KEY_W))
      input.y -= 1;
    if (IsKeyDown(KEY_S))
      input.y += 1;
    if (IsKeyDown(KEY_A))
      input.x -= 1;
    if (IsKeyDown(KEY_D))
      input.x += 1;
    break;
  case 2:
    // Controles del segundo jugador
    if (IsKeyDown(KEY_UP))
      input.y -= 1;
    if (IsKeyDown(KEY_DOWN))
      input.y += 1;
    if (IsKeyDown(KEY_LEFT))
      input.x -= 1;
    if (IsKeyDown(KEY_RIGHT))
      input.x += 1;
  default:
    break;
  }

  Vector2 move = Vector2Scale(Vector2Normalize(input), player->speed * delta);

  player->direction = Vector2Normalize(input);

  // Primero mover en X
  Vector2 moveX = {move.x, 0};
  Collision colX = CheckCollisionWithMap(moveX, &player->position,
                                         PLAYER_SIZE / 2, false, 0);
  if (!colX.hasColided) {
    player->position.x += moveX.x;
  }

  // Luego mover en Y
  Vector2 moveY = {0, move.y};
  Collision colY = CheckCollisionWithMap(moveY, &player->position,
                                         PLAYER_SIZE / 2, false, 0);
  if (!colY.hasColided) {
    player->position.y += moveY.y;
  }
}
