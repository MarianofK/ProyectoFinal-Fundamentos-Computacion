#include "definitions.h"
#include "raylib.h"

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
#define NUM_SHOOTS 20
#define NUM_MAX_ENEMIES 20
#define SHOOT_X_SIZE 60
#define SHOOT_Y_SIZE 40
#define ENEMY_X_SIZE 100
#define ENEMY_Y_SIZE 100
#define KILL_POINTS 20

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------

typedef struct Player {
  Rectangle rec;
  Vector2 speed;
  Texture texture_image;
  bool isFirst;
  int score;
  int num;
} Player;

typedef struct Enemy {
  Rectangle rec;
  Vector2 speed;
  bool active;
  Texture texture_image;
} Enemy;

typedef struct Shoot {
  Rectangle rec;
  Vector2 speed;
  bool active;
  Color color;
  Texture texture_image;
} Shoot;

//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
static bool gameOver = false;
static bool victory = false;

static Shoot shoot[NUM_SHOOTS] = {0};
static int times_shoot = 0;

static int activeEnemies = 0;

//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
static void InitGame(Player *, Enemy *, Image, Image, Image); // Initialize game
static void UpdateGame(Player *, Enemy *); // Update game (one frame)
static void DrawGAME(Player *, Enemy *, Texture,
                     Font);   // Draw game (one frame)
static void UnloadGame(void); // Unload game
static void UpdateDrawFrame(Player *, Enemy *, Texture,
                            Font); // Update and Draw (one frame)

//------------------------------------------------------------------------------------
// Mini game entry point
//------------------------------------------------------------------------------------
int mini_game(void) {

  // Player declaration
  Player player_1 = {0};
  Player player_2 = {0};

  // Targets
  Enemy enemy_p1[NUM_MAX_ENEMIES] = {0};
  Enemy enemy_p2[NUM_MAX_ENEMIES] = {0};

  // Player textures
  Image img_p1 = LoadImage(ASSETS_PATH "/player/arquero_p1.png");
  ImageResize(&img_p1, 70, 70);

  Image img_p2 = LoadImage(ASSETS_PATH "/player/arquero_p2.png");
  ImageResize(&img_p2, 70, 70);

  // Shoot textures
  Image img_shoot = LoadImage(ASSETS_PATH "/player/flechita.png");
  ImageResize(&img_shoot, SHOOT_X_SIZE, SHOOT_Y_SIZE);

  // Enemy textures
  Image img_enemy = LoadImage(ASSETS_PATH "/mini-game/enemy.png");
  ImageResize(&img_enemy, ENEMY_X_SIZE, ENEMY_Y_SIZE);

  // Mini game textures
  Texture background = LoadTexture(ASSETS_PATH "/mini-game/background.png");
  Font status_font = LoadFont(ASSETS_PATH "/mini-game/status_font.png");

  // Player numbers
  player_1.num = 1;
  player_2.num = 2;

  // Initialization for players
  InitGame(&player_1, enemy_p1, img_shoot, img_enemy, img_p1);
  InitGame(&player_2, enemy_p2, img_shoot, img_enemy, img_p2);

  // Main game loop
  // First: player 1 till game end
  while (player_1.isFirst) {
    // Update and Draw
    UpdateDrawFrame(&player_1, enemy_p1, background, status_font);
  }

  // Second: player 2 till game end
  while (player_2.isFirst) {
    // Update and Draw
    UpdateDrawFrame(&player_2, enemy_p2, background, status_font);
  }
  // Update scores
  score_player1 += player_1.score;
  score_player2 += player_2.score;

  // De-Initialization
  // Players
  UnloadImage(img_p1);
  UnloadTexture(player_1.texture_image);
  UnloadImage(img_p2);
  UnloadTexture(player_2.texture_image);
  // Shoots
  UnloadImage(img_shoot);
  for (int i = 0; i < NUM_SHOOTS; i++)
    UnloadTexture(shoot[i].texture_image);
  // Enemy
  UnloadImage(img_enemy);
  for (int i = 0; i < NUM_MAX_ENEMIES; i++) {
    UnloadTexture(enemy_p1[i].texture_image);
    UnloadTexture(enemy_p2[i].texture_image);
  }
  // Mini-game
  UnloadTexture(background);
  // Font
  UnloadFont(status_font);

  // Goto
  state = STATE_ARCH_SELECTION;

  return 0;
}

//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------

// Initialize game variables
void InitGame(Player *player, Enemy *enemy, Image img_shoot, Image img_enemy,
              Image img_p) {
  // Initialize game variables
  times_shoot = 0;
  activeEnemies = NUM_MAX_ENEMIES;

  // Initialize player
  player->rec.width = 70;
  player->rec.height = 70;
  player->rec.x = 20;
  player->rec.y = (float)screenHeight / 2;
  player->speed.x = 5;
  player->speed.y = 5;
  player->isFirst = true;
  player->score = 0;
  player->texture_image = LoadTextureFromImage(img_p);

  // Initialize enemies
  for (int i = 0; i < NUM_MAX_ENEMIES; i++) {
    enemy[i].rec.width = 10;
    enemy[i].rec.height = 40;
    enemy[i].rec.x = GetRandomValue(screenWidth, screenWidth + 1000);
    enemy[i].rec.y = GetRandomValue(120, screenHeight - enemy[i].rec.height);
    enemy[i].speed.x = 5;
    enemy[i].speed.y = 5;
    enemy[i].active = true;
    enemy[i].texture_image = LoadTextureFromImage(img_enemy);
  }

  // Initialize shoots
  for (int i = 0; i < NUM_SHOOTS; i++) {
    // Player
    shoot[i].rec.x = player->rec.x;
    shoot[i].rec.y = player->rec.y + (player->rec.height / 4);
    shoot[i].rec.width = SHOOT_X_SIZE;
    shoot[i].rec.height = SHOOT_Y_SIZE;
    shoot[i].speed.x = 7;
    shoot[i].speed.y = 0;
    shoot[i].active = false;
    shoot[i].color = MAROON;
    shoot[i].texture_image = LoadTextureFromImage(img_shoot);
  }
}

// Update game (one frame)
void UpdateGame(Player *player, Enemy *enemy) {
  if (!gameOver && activeEnemies > 0) {
    // Player movement
    if (IsKeyDown(KEY_D))
      player->rec.x += player->speed.x;
    if (IsKeyDown(KEY_A))
      player->rec.x -= player->speed.x;
    if (IsKeyDown(KEY_W))
      player->rec.y -= player->speed.y;
    if (IsKeyDown(KEY_S))
      player->rec.y += player->speed.y;

    // Player collision with enemy
    for (int i = 0; i < NUM_MAX_ENEMIES; i++) {
      if (CheckCollisionRecs(player->rec, enemy[i].rec)) {
        gameOver = true;
      }
    }

    // Enemy behaviour
    for (int i = 0; i < NUM_MAX_ENEMIES; i++) {
      if (enemy[i].active) {
        enemy[i].rec.x -= enemy[i].speed.x;

        // Enemy vs wall
        if (enemy[i].rec.x < 0) {
          enemy[i].active = false;
          activeEnemies--;
        }
      }
    }

    // Wall behaviour vs Player
    if (player->rec.x >= MeasureText("player number:", 40))
      player->rec.x = MeasureText("player number:", 40);
    if (player->rec.x + player->rec.width >= screenWidth)
      player->rec.x = screenWidth - player->rec.width;
    if (player->rec.y <= 120)
      player->rec.y = 120;
    if (player->rec.y + player->rec.height >= screenHeight)
      player->rec.y = screenHeight - player->rec.height;

    // Shoot initialization for player
    if (IsKeyPressed(KEY_SPACE) && times_shoot < NUM_SHOOTS) {
      shoot[times_shoot].rec.x = player->rec.x;
      shoot[times_shoot].rec.y = player->rec.y + (player->rec.height / 4);
      shoot[times_shoot].active = true;
      times_shoot++;
    }

    // Shoot logic
    for (int i = 0; i < NUM_SHOOTS; i++) {
      if (shoot[i].active) {
        // Movement
        shoot[i].rec.x += shoot[i].speed.x;

        // Collision with enemy
        for (int j = 0; j < NUM_MAX_ENEMIES; j++) {
          if (enemy[j].active) {
            if (CheckCollisionRecs(shoot[i].rec, enemy[j].rec)) {
              shoot[i].active = false;
              enemy[j].active = false;
              activeEnemies--;
              player->score += KILL_POINTS;
            }

            if (shoot[i].rec.x + shoot[i].rec.width >= screenWidth) {
              shoot[i].active = false;
            }
          }
        }
      }
    }
  } else {
    if (IsKeyPressed(KEY_ENTER)) {
      gameOver = false;
      player->isFirst = false;
      activeEnemies = NUM_MAX_ENEMIES;
      for (int i = 0; i < times_shoot; i++)
        shoot[i].active = false;
      times_shoot = 0;
    }
  }
}

// Draw game (one frame)
void DrawGame(Player *player, Enemy *enemy, Texture background,
              Font status_font) {
  BeginDrawing();

  ClearBackground(RAYWHITE);
  DrawTexture(background, 0, 0, WHITE);

  if (!gameOver && activeEnemies > 0) {
    DrawTexture(player->texture_image, player->rec.x, player->rec.y, WHITE);

    for (int i = 0; i < NUM_MAX_ENEMIES; i++) {
      if (enemy[i].active)
        DrawTexture(enemy[i].texture_image, enemy[i].rec.x, enemy[i].rec.y,
                    WHITE);
    }

    for (int i = 0; i < NUM_SHOOTS; i++) {
      if (shoot[i].active)
        DrawTexture(shoot[i].texture_image, shoot[i].rec.x, shoot[i].rec.y,
                    WHITE);
    }

    // Status box
    DrawTextEx(status_font, TextFormat("%04i", player->score),
               (Vector2){20, 20}, 40, 2, WHITE);
    DrawTextEx(status_font, TextFormat("PLAYER NUMBER %i", player->num),
               (Vector2){20, 60}, 45, -2.7f, WHITE);
    DrawTextEx(
        status_font, TextFormat("TARGETS LEFT: %i", activeEnemies),
        (Vector2){screenWidth - MeasureText("TARGETS LEFT: %i", 40) - 50, 20},
        45, -2.7f, WHITE);
    DrawTextEx(
        status_font, TextFormat("ARROW LEFT: %i", NUM_SHOOTS - times_shoot),
        (Vector2){screenWidth - MeasureText("ARROW LEFT: %i", 40) - 50, 60}, 45,
        -2.7f, WHITE);
  } else {
    if (player->num == 1) {
      DrawTextEx(
          status_font, "TERMINO TU TURNO, JUGADOR 2 PRESIONA ENTER",
          (Vector2){(float)screenWidth / 2 -
                        (float)MeasureText(
                            "TERMINO TU TURNO, JUGADOR 2 PRESIONA ENTER", 40) /
                            2,
                    (float)screenHeight / 2 - 50},
          45, -2.7f, WHITE);

    } else if (player->num == 2) {
      DrawTextEx(
          status_font, "TERMINO TU TURNO PRESIONA ENTER PARA TERMINAR",
          (Vector2){
              (float)screenWidth / 2 -
                  (float)MeasureText(
                      "TERMINO TU TURNO PRESIONA ENTER PARA TERMINAR", 40) /
                      2,
              (float)screenHeight / 2 - 50},
          45, -2.7f, WHITE);
    }
  }
  EndDrawing();
}

// Update and Draw (one frame)
void UpdateDrawFrame(Player *player, Enemy *enemy, Texture background,
                     Font status_font) {
  UpdateGame(player, enemy);
  DrawGame(player, enemy, background, status_font);
}
