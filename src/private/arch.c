#include "arch.h"
#include "definitions.h"
#include "player.h"

Arch *arch1 = NULL, *arch2 = NULL, *arch3 = NULL;

Rectangle card1 = {0 , 0, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT};
Rectangle card2 = {0 , 0, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT};
Rectangle card3 = {0 , 0, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT};

Color selectedColor = (Color){0, 0, 0, 10};

void InitArchs(){
    Image img = LoadImage(ASSETS_PATH "/player/arch.png");
    ImageResize(&img, PLAYER_SIZE - 10, PLAYER_SIZE - 10);

    Arch *initial1 = malloc(sizeof(Arch));
    *initial1 = (Arch){ "Fuego", 0, 0, LoadTextureFromImage(img), };

    Arch *initial2 = malloc(sizeof(Arch));
    *initial2 = (Arch){ "Energia", 0, 0, LoadTextureFromImage(img), };

    Arch *initial3 = malloc(sizeof(Arch));
    *initial3 = (Arch){ "Veneno", 0, 0, LoadTextureFromImage(img), };

    UnloadImage(img);
    
    arch1 = initial1;
    arch2 = initial2;
    arch3 = initial3;
}

void DrawArch(Arch *arch, Vector2 playerPosition, Vector2 playerDirection){

    // Calcular ángulo en radianes, luego convertir a grados
    float angle = atan2f(playerDirection.y, playerDirection.x) * RAD2DEG;

    DrawTexturePro(
        arch->texture, 
        (Rectangle){0, 0, arch->texture.width, arch->texture.height},
        (Rectangle){playerPosition.x, playerPosition.y + 10, arch->texture.width, arch->texture.height},
        (Vector2){arch->texture.width / 2, arch->texture.height / 2},
        angle,
        WHITE
    );
}

void DrawSelectionArch(int x, int y, int playerNumber){

    Vector2 mouse = GetMousePosition();

    card1.x = x - ARCH_CARD_WIDTH * 1.6;
    card1.y = y;

    card2.x = x - ARCH_CARD_WIDTH * 0.5;
    card2.y = y;

    card3.x = x + ARCH_CARD_WIDTH * 0.6;
    card3.y = y;

    if(player1.currentArch == arch1 || player2.currentArch == arch1){
        DrawRectangleRec(card1, selectedColor); 
    } else {
        DrawRectangleRec(card1, LIGHTGRAY);
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, card1)){
            if(playerNumber == 1){
                player1.currentArch = arch1;
                selection = SELECTION_PLAYER_2;
            } else {
                player2.currentArch = arch1;
                state = STATE_GAME;
                selection = SELECTION_PLAYER_1;
            }
        }
    }
    DrawTexture(arch1->texture, card1.x, card1.y, WHITE);
    DrawText(arch1->name, card1.x + 45, card1.y + ARCH_CARD_HEIGHT - 30, 20, BLACK);

    if(player1.currentArch == arch2 || player2.currentArch == arch2){
        DrawRectangleRec(card2, selectedColor); 
    } else {
        DrawRectangleRec(card2, LIGHTGRAY);
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, card2)){
            if(playerNumber == 1){
                player1.currentArch = arch2;
                selection = SELECTION_PLAYER_2;
            } else {
                player2.currentArch = arch2;
                state = STATE_GAME;
                selection = SELECTION_PLAYER_1;
            }
        }
    }
    DrawTexture(arch2->texture, card2.x, card2.y, WHITE);
    DrawText(arch2->name, card2.x + 25, card2.y + ARCH_CARD_HEIGHT - 30, 20, BLACK);

    if(player1.currentArch == arch3 || player2.currentArch == arch3){
        DrawRectangleRec(card3, selectedColor); 
    } else {
        DrawRectangleRec(card3, LIGHTGRAY);
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, card3)){
            if(playerNumber == 1){
                player1.currentArch = arch3;
                selection = SELECTION_PLAYER_2;
            } else {
                player2.currentArch = arch3;
                state = STATE_GAME;
                selection = SELECTION_PLAYER_1;
            }
        }
    }
    DrawTexture(arch3->texture, card3.x, card3.y, WHITE);
    DrawText(arch3->name, card3.x + 35, card3.y + ARCH_CARD_HEIGHT - 30, 20, BLACK);
}

void DrawArchsToUpgrade(int x, int y, int playerNumber){

    Vector2 mouse = GetMousePosition();

    card1.x = x - ARCH_CARD_WIDTH * 1.2;
    card1.y = y;
    DrawRectangleRec(card1, selectedColor); 

    card2.x = x - ARCH_CARD_WIDTH * 0.2;
    card2.y = y;
    DrawRectangleRec(card2, selectedColor); 

    switch (playerNumber){
    case 1:
        if(player1.currentArch->previous != NULL && player1.currentArch->next != NULL){
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, card1)){
                player1.currentArch = player1.currentArch->previous;
                selection = SELECTION_PLAYER_2;
            }
            DrawTexture(player1.currentArch->previous->texture, card1.x, card1.y, WHITE);
            DrawText(player1.currentArch->name, card1.x + 35, card1.y + ARCH_CARD_HEIGHT - 30, 20, BLACK);
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, card2)){
                player1.currentArch = player1.currentArch->next;
                selection = SELECTION_PLAYER_2;
            }
            DrawTexture(player1.currentArch->next->texture, card2.x, card2.y, WHITE);
            DrawText(player1.currentArch->name, card2.x + 35, card2.y + ARCH_CARD_HEIGHT - 30, 20, BLACK);
        } else {
            selection = SELECTION_PLAYER_2;
        }
        break;

    case 2:
        if(player2.currentArch->previous != NULL && player2.currentArch->next != NULL){
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, card1)){
                player2.currentArch = player2.currentArch->previous;
                state = STATE_GAME;
                selection = SELECTION_PLAYER_1;
            }
            DrawTexture(player2.currentArch->previous->texture, card1.x, card1.y, WHITE);
            DrawText(player2.currentArch->name, card1.x + 35, card1.y + ARCH_CARD_HEIGHT - 30, 20, BLACK);
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, card2)){
                player2.currentArch = player2.currentArch->next;
                state = STATE_GAME;
                selection = SELECTION_PLAYER_1;
            }
            DrawTexture(player2.currentArch->next->texture, card2.x, card2.y, WHITE);
            DrawText(player2.currentArch->name, card2.x + 35, card2.y + ARCH_CARD_HEIGHT - 30, 20, BLACK);
        } else {
            state = STATE_GAME;
            selection = SELECTION_PLAYER_1;
        }
        break;

    default:
        break;
    }
}