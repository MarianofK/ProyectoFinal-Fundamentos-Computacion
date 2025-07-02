#include "menu.h"
#include "definitions.h"

Rectangle btnOptions = {0, 0, rectangleWidth, rectangleHeight};
Rectangle btnExit = {0, 0, rectangleWidth, rectangleHeight};

Rectangle btnContinue = {0, 0, rectangleWidth, rectangleHeight};
Rectangle btnMainMenu = {0, 0, rectangleWidth, rectangleHeight};

Texture2D backgroundMenu;
Texture2D background;

Texture2D btnImageHover;
Texture2D btnImage;

void InitMenu(){
  Image bg = LoadImage(ASSETS_PATH "/ui/background/bg_menu.png");
  backgroundMenu = LoadTextureFromImage(bg);
  UnloadImage(bg);

  Image bg2 = LoadImage(ASSETS_PATH "/ui/background/bg.png");
  background = LoadTextureFromImage(bg2);
  UnloadImage(bg2);

  Image btnH = LoadImage(ASSETS_PATH "/ui/button/btn_hover.png");
  ImageResize(&btnH, rectangleWidth, rectangleHeight);
  btnImageHover = LoadTextureFromImage(btnH);
  UnloadImage(btnH);

  Image btnI = LoadImage(ASSETS_PATH "/ui/button/btn.png");
  ImageResize(&btnI, rectangleWidth, rectangleHeight);
  btnImage = LoadTextureFromImage(btnI);
  UnloadImage(btnI);
}

void DrawMenu(int x, int y) {

  DrawTexturePro(
    backgroundMenu,
    (Rectangle){0, 0, (float)backgroundMenu.width, (float)backgroundMenu.height},
    (Rectangle){0, 0, (float)screenWidth, (float)screenHeight},
    (Vector2){0, 0},
    0.0f,
    WHITE
  );

  DrawTextCentered("Battlearcher", x, y - 120, 30, WHITE);

  if (DrawButton("Empezar", btnImage, btnImageHover, (Rectangle){x - rectangleWidth / 2, y - 60, rectangleWidth, rectangleHeight}, WHITE)) {
    bSelected = false;
    InitPlayer(&player1, (3 * TILE_SIZE) / 2, (3 * TILE_SIZE) / 2, 200.f, 1);
    InitPlayer(&player2, TILE_SIZE * (MAP_WIDTH - 1.5), TILE_SIZE * (MAP_HEIGHT - 1.5), 200.f, 2);
    PlayLevelMusic(ASSETS_PATH "/sounds/nivel_1.wav");
    player1.currentArch = NULL;
    player2.currentArch = NULL;
    state = STATE_MINI_GAME;
  }

  if(DrawButton("Ajustes", btnImage, btnImageHover, (Rectangle){x - rectangleWidth / 2, y, rectangleWidth, rectangleHeight}, WHITE)){
    state = STATE_SETTINGS;
  }

  if(DrawButton("Salir", btnImage, btnImageHover, (Rectangle){x - rectangleWidth / 2, y + 60, rectangleWidth, rectangleHeight}, WHITE)){
    state = STATE_EXIT;
  }
}

void DrawEndMenu(int x, int y) {

  DrawTexturePro(
    background,
    (Rectangle){0, 0, (float)background.width, (float)background.height},
    (Rectangle){0, 0, (float)screenWidth, (float)screenHeight},
    (Vector2){0, 0},
    0.0f,
    WHITE
  );

  DrawTextCentered(TextFormat("El jugador %d ganó", player1.life <= 0   ? 2 : player2.life <= 0 ? 1 : 0), x, y - 50, 20, BLACK);

  if(DrawButton("Continuar", btnImage, btnImageHover, (Rectangle){x - rectangleWidth / 2, y, rectangleWidth, rectangleHeight}, WHITE)){
    InitPlayer(&player1, (3 * TILE_SIZE) / 2, (3 * TILE_SIZE) / 2, 200.f, 1);
    InitPlayer(&player2, TILE_SIZE * (MAP_WIDTH - 1.5), TILE_SIZE * (MAP_HEIGHT - 1.5), 200.f, 2);
    state = STATE_MINI_GAME;
  }

  if(DrawButton("Menu", btnImage, btnImageHover, (Rectangle){x - rectangleWidth / 2, y + 60, rectangleWidth, rectangleHeight}, WHITE)){
    state = STATE_MENU;
  }
}
