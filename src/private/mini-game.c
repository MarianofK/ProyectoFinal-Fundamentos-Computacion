#include "definitions.h"
#include "raylib.h"

#define MAX_FRAME_SPEED 15
#define MIN_FRAME_SPEED 1

int mini_game(int screenWidth, int screenHeight) {

  Texture2D player1 = LoadTexture(ASSETS_PATH "player/scarfy.png");
  Texture2D player2 = LoadTexture(ASSETS_PATH "player/scarfy.png");

  Vector2 position_player1 = {350.0f, 280.0f};
  Vector2 position_player2 = {350.0f, 280.0f};

  Rectangle frameRecs_player1 = {0.0f, 0.0f, (float)player1.width / 6,
                                 (float)player1.height};
  Rectangle frameRecs_player2 = {0.0f, 0.0f, (float)player2.width / 6,
                                 (float)player2.height};

  // Frames
  int currentFrame = 0;
  int framesCounter = 0;
  int framesSpeed = 10; // Number of spritesheet frames shown by second

  RenderTexture screenCamera1 =
      LoadRenderTexture(screenWidth / 2, screenHeight);
  RenderTexture screenCamera2 =
      LoadRenderTexture(screenWidth / 2, screenHeight);

  // Build a flipped rectangle the size of the split view to use for drawing
  // later
  Rectangle splitScreenRect = {0.0f, 0.0f, (float)screenCamera1.texture.width,
                               (float)-screenCamera1.texture.height};

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!IsKeyPressed(KEY_ESCAPE)) // Detect window close button or ESC key
  {
    // Update players
    framesCounter++;

    if (framesCounter >= (60 / framesSpeed)) {
      framesCounter = 0;
      currentFrame++;

      if (currentFrame > 5)
        currentFrame = 0;

      frameRecs_player1.x = (float)currentFrame * (float)player1.width / 6;
      frameRecs_player2.x = (float)currentFrame * (float)player2.width / 6;
    }

    //----------------------------------------------------------------------------------
    // Draw player 1
    //----------------------------------------------------------------------------------
    BeginTextureMode(screenCamera1);

    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawTextureRec(player1, frameRecs_player1, position_player1,
                   WHITE); // Draw part of the texture

    EndDrawing();

    // Top part
    DrawRectangle(0, 0, screenCamera1.texture.width, 100, Fade(RAYWHITE, 0.6f));
    DrawRectangle(screenCamera1.texture.width / 2, 10, 80, 80, Fade(RED, 0.6f));
    DrawRectangle((screenCamera1.texture.width / 2) + 10, 20, 60, 60,
                  Fade(WHITE, 100));

    EndTextureMode();

    // END player 1

    //----------------------------------------------------------------------------------
    // Draw player 2
    //----------------------------------------------------------------------------------

    BeginTextureMode(screenCamera2);

    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawTextureRec(player2, frameRecs_player2, position_player2,
                   WHITE); // Draw part of the texture

    EndDrawing();

    // Top part
    DrawRectangle(0, 0, screenCamera2.texture.width, 100, Fade(RAYWHITE, 0.6f));
    DrawRectangle(screenCamera2.texture.width / 2, 10, 80, 80, Fade(RED, 0.6f));
    DrawRectangle((screenCamera2.texture.width / 2) + 10, 20, 60, 60,
                  Fade(WHITE, 100));

    EndTextureMode();

    // Draw both views render textures to the screen side by side
    BeginDrawing();
    ClearBackground(BLACK);

    DrawTextureRec(screenCamera1.texture, splitScreenRect, (Vector2){0, 0},
                   WHITE);
    DrawTextureRec(screenCamera2.texture, splitScreenRect,
                   (Vector2){screenWidth / 2.0f, 0}, WHITE);

    DrawRectangle(GetScreenWidth() / 2 - 2, 0, 4, GetScreenHeight(), LIGHTGRAY);
    EndDrawing();
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  UnloadRenderTexture(screenCamera1); // Unload render texture
  UnloadRenderTexture(screenCamera2); // Unload render texture
  UnloadTexture(player1);
  UnloadTexture(player2);
  state = STATE_GAME;
  return 0;
}
