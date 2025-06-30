#include "definitions.h"
#include "raylib.h"

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
#define NUM_SHOOTS 50
#define NUM_MAX_ENEMIES 50

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------

typedef struct Player {
  Rectangle rec;
  Vector2 speed;
  Color color;
  bool isFirst;
  int score;
  int num;
} Player;

typedef struct Enemy {
  Rectangle rec;
  Vector2 speed;
  bool active;
  Color color;
} Enemy;

typedef struct Shoot {
  Rectangle rec;
  Vector2 speed;
  bool active;
  Color color;
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
static void InitGame(Player *, Enemy *);        // Initialize game
static void UpdateGame(Player *, Enemy *);      // Update game (one frame)
static void DrawGAME(Player *, Enemy *);        // Draw game (one frame)
static void UnloadGame(void);                   // Unload game
static void UpdateDrawFrame(Player *, Enemy *); // Update and Draw (one frame)

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

  // Player colors (textures)
  player_1.color = BLACK;
  player_2.color = BLACK;

  // Player numbers
  player_1.num = 1;
  player_2.num = 2;

  // Initialization for players
  InitGame(&player_1, enemy_p1);
  InitGame(&player_2, enemy_p2);

  // Main game loop
  // First: player 1 till game end
  while (player_1.isFirst) {
    // Update and Draw
    UpdateDrawFrame(&player_1, enemy_p1);
  }

  // Second: player 2 till game end
  while (player_2.isFirst) {
    // Update and Draw
    UpdateDrawFrame(&player_2, enemy_p2);
  }
  // Update scores
  score_player1 += player_1.score;
  score_player2 += player_2.score;

  // De-Initialization
  UnloadGame(); // Unload loaded data (textures, sounds, models...)
  state = STATE_ARCH_SELECTION;

  return 0;
}

//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------

// Initialize game variables
void InitGame(Player *player, Enemy *enemy) {
  // Initialize game variables
  times_shoot = 0;
  activeEnemies = NUM_MAX_ENEMIES;

  // Initialize player
  player->rec.x = 20;
  player->rec.y = (float)screenHeight / 2;
  player->rec.width = 25;
  player->rec.height = 25;
  player->speed.x = 5;
  player->speed.y = 5;
  player->isFirst = true;
  player->score = 0;

  // Initialize enemies
  for (int i = 0; i < NUM_MAX_ENEMIES; i++) {
    enemy[i].rec.width = 10;
    enemy[i].rec.height = 10;
    enemy[i].rec.x = GetRandomValue(screenWidth, screenWidth + 1000);
    enemy[i].rec.y = GetRandomValue(enemy[i].rec.height - 120,
                                    screenHeight - enemy[i].rec.height);
    enemy[i].speed.x = 5;
    enemy[i].speed.y = 5;
    enemy[i].active = true;
    enemy[i].color = GRAY;
  }

  // Initialize shoots
  for (int i = 0; i < NUM_SHOOTS; i++) {
    // Player
    shoot[i].rec.x = player->rec.x;
    shoot[i].rec.y = player->rec.y + player->rec.height / 4;
    shoot[i].rec.width = 10;
    shoot[i].rec.height = 5;
    shoot[i].speed.x = 7;
    shoot[i].speed.y = 0;
    shoot[i].active = false;
    shoot[i].color = RED;
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
        // TODO handle shots maybe here
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
    if (player->rec.x >= MeasureText("Jugador:", 40))
      player->rec.x = MeasureText("Jugador:", 40);
    if (player->rec.x + player->rec.width >= screenWidth)
      player->rec.x = screenWidth - player->rec.width;
    if (player->rec.y <= 120)
      player->rec.y = 120;
    if (player->rec.y + player->rec.height >= screenHeight)
      player->rec.y = screenHeight - player->rec.height;

    // Shoot initialization for player
    if (IsKeyPressed(KEY_SPACE) && times_shoot < NUM_SHOOTS) {
      shoot[times_shoot].rec.x = player->rec.x;
      shoot[times_shoot].rec.y = player->rec.y + player->rec.height / 4;
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
              player->score += 100;
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
      times_shoot = 0;
    }
  }
}

// Draw game (one frame)
void DrawGame(Player *player, Enemy *enemy) {
  BeginDrawing();

  ClearBackground((Color){240, 240, 240, 255});

  if (!gameOver && activeEnemies > 0) {
    DrawRectangleRec(player->rec, player->color);

    for (int i = 0; i < NUM_MAX_ENEMIES; i++) {
      if (enemy[i].active)
        DrawRectangleRec(enemy[i].rec, enemy[i].color);
    }

    for (int i = 0; i < NUM_SHOOTS; i++) {
      if (shoot[i].active)
        DrawRectangleRec(shoot[i].rec, shoot[i].color);
    }

    // Player max distance
    DrawRectangle(MeasureText("Jugador:", 40) + player->rec.width, 120, 5,
                  screenHeight - 120, BLACK);

    // Status box
    DrawRectangle(0, 0, screenWidth, 120, LIGHTGRAY);
    DrawText(TextFormat("%04i", player->score), 20, 20, 40, BLACK);
    DrawText(TextFormat("Jugador: %i", player->num), 20, 60, 40, BLACK);
    DrawText(TextFormat("Enemigos: %i", activeEnemies),
             screenWidth - MeasureText("Enemigos: %i", 40) - 50, 20, 40,
             BLACK);
    DrawText(TextFormat("Municion: %i", NUM_SHOOTS - times_shoot),
             screenWidth - MeasureText("Enemigos: %i", 40) - 50, 60, 40,
             BLACK);

    if (victory)
      DrawText("Ganaste", screenWidth / 2 - MeasureText("Ganaste", 40) / 2,
               screenHeight / 2 - 40, 40, BLACK);
  } else {
    if (player->num == 1) {
      DrawText(
          "TERMINO TU TURNO, JUGADOR 2 PRESIONA [ENTER]",
          GetScreenWidth() / 2 -
              MeasureText("TERMINO TU TURNO, JUGADOR 2 PRESIONA [ENTER]", 20) /
                  2,
          GetScreenHeight() / 2 - 50, 20, BLACK);

    } else if (player->num == 2) {
      DrawText("TERMINO TU TURNO, PRESIONA [ENTER] PARA TERMINAR",
               GetScreenWidth() / 2 -
                   MeasureText(
                       "TERMINO TU TURNO, PRESIONA [ENTER] PARA TERMINAR", 20) /
                       2,
               GetScreenHeight() / 2 - 50, 20, BLACK);
    }
  }
  EndDrawing();
}

// Unload game variables
void UnloadGame(void) {
  // TODO: Unload all dynamic loaded data (textures, sounds, models...)
}

// Update and Draw (one frame)
void UpdateDrawFrame(Player *player, Enemy *enemy) {
  UpdateGame(player, enemy);
  DrawGame(player, enemy);
}
