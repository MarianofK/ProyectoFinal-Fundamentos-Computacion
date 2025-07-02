#include "arch.h"
#include "definitions.h"
#include "player.h"
#include "functions.h"
#include "menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Arch *arch1 = NULL, *arch2 = NULL, *arch3 = NULL;

Rectangle card1 = {0, 0, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT};
Rectangle card2 = {0, 0, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT};
Rectangle card3 = {0, 0, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT};

Color selectedColor = (Color){0, 0, 0, 10};

Texture2D cardImage;
Texture2D cardImageBloqued;

bool bSelected = false;

void InitArchs() {

    Image cardImg = LoadImage(ASSETS_PATH "/ui/card/card_image.png");
    ImageResize(&cardImg, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT);
    cardImage = LoadTextureFromImage(cardImg);
    UnloadImage(cardImg);

    Image cardImgBloqued = LoadImage(ASSETS_PATH "/ui/card/card_darked.png");
    ImageResize(&cardImgBloqued, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT);
    cardImageBloqued = LoadTextureFromImage(cardImgBloqued);
    UnloadImage(cardImgBloqued);

    arch1 = LoadArchTreeFromCSV(ASSETS_PATH "/data/arch_tree1.csv");
    arch2 = LoadArchTreeFromCSV(ASSETS_PATH "/data/arch_tree2.csv");
    arch3 = LoadArchTreeFromCSV(ASSETS_PATH "/data/arch_tree3.csv");
}

void DrawArch(Arch *arch, Vector2 playerPosition, Vector2 playerDirection) {
    float angle = atan2f(playerDirection.y, playerDirection.x) * RAD2DEG;

    DrawTexturePro(
        arch->arch,
        (Rectangle){0, 0, arch->arch.width, arch->arch.height},
        (Rectangle){playerPosition.x, playerPosition.y + 10, arch->arch.width, arch->arch.height},
        (Vector2){arch->arch.width / 2, arch->arch.height / 2},
        angle, WHITE
    );
}

void DrawSelectionArch(int x, int y, int playerNumber) {

    DrawTexturePro(
        background,
        (Rectangle){0, 0, (float)background.width, (float)background.height},
        (Rectangle){0, 0, (float)screenWidth, (float)screenHeight},
        (Vector2){0, 0},
        0.0f,
        WHITE
    );

    if(bSelected) {
        state = STATE_ARCH_UPGRADE;
        selection = SELECTION_PLAYER_1;
        return;
    }

    card1.x = x - ARCH_CARD_WIDTH * 1.6;
    card1.y = y;

    card2.x = x - ARCH_CARD_WIDTH * 0.5;
    card2.y = y;

    card3.x = x + ARCH_CARD_WIDTH * 0.6;
    card3.y = y;

    switch (playerNumber)
    {
    case 1:
        if(player2.currentArch != arch1){
            if(DrawCard(cardImage, (Rectangle){card1.x, card1.y, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT})){
                player1.currentArch = arch1;
                selection = SELECTION_PLAYER_2;
            }
        } else {
            DrawCard(cardImageBloqued, (Rectangle){card1.x, card1.y, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT});
        }
        if(player2.currentArch != arch2){
            if(DrawCard(cardImage, (Rectangle){card2.x, card2.y, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT})){
                player1.currentArch = arch2;
                selection = SELECTION_PLAYER_2;
            }
        } else {
            DrawCard(cardImageBloqued, (Rectangle){card2.x, card2.y, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT});
        }
        if(player2.currentArch != arch3){
            if(DrawCard(cardImage, (Rectangle){card3.x, card3.y, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT})){
                player1.currentArch = arch3;
                selection = SELECTION_PLAYER_2;
            }
        } else {
            DrawCard(cardImageBloqued, (Rectangle){card3.x, card3.y, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT});
        }
        break;
    case 2:
        if(player1.currentArch != arch1){
            if(DrawCard(cardImage, (Rectangle){card1.x, card1.y, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT})){
                player2.currentArch = arch1;
                bSelected = true;
                state = STATE_ARCH_UPGRADE;
                selection = SELECTION_PLAYER_1;
            }
        } else {
            DrawCard(cardImageBloqued, (Rectangle){card1.x, card1.y, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT});
        }
        if(player1.currentArch != arch2){
            if(DrawCard(cardImage, (Rectangle){card2.x, card2.y, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT})){
                player2.currentArch = arch2;
                bSelected = true;
                state = STATE_ARCH_UPGRADE;
                selection = SELECTION_PLAYER_1;
            }
        } else {
            DrawCard(cardImageBloqued, (Rectangle){card2.x, card2.y, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT});
        }
        if(player1.currentArch != arch3){
            if(DrawCard(cardImage, (Rectangle){card3.x, card3.y, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT})){
                player2.currentArch = arch3;
                bSelected = true;
                state = STATE_ARCH_UPGRADE;
                selection = SELECTION_PLAYER_1;
            }
        } else {
            DrawCard(cardImageBloqued, (Rectangle){card3.x, card3.y, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT});
        }
        break;

    default:
        break;
    }

    DrawTextCentered("Seleccion de arcos", x, 50, 30, WHITE);
    DrawTextCentered(TextFormat("Jugador %d", playerNumber), x, 120, 20, WHITE);

    // Tarjeta 1
    DrawTextureCentered(arch1->texture, card1.x + card1.width / 2, card1.y +  80, WHITE);
    DrawTextCentered(arch1->name, card1.x + card1.width / 2, card1.y + ARCH_CARD_HEIGHT - 50, 25, WHITE);

    // Tarjeta 2
    DrawTextureCentered(arch2->texture, card2.x + card2.width / 2, card2.y + 80, WHITE);
    DrawTextCentered(arch2->name, card2.x + card2.width / 2, card2.y + ARCH_CARD_HEIGHT - 50, 25, WHITE);

    // Tarjeta 3
    DrawTextureCentered(arch3->texture, card3.x + card3.width / 2, card3.y + 80, WHITE);
    DrawTextCentered(arch3->name, card3.x + card3.width / 2, card3.y + ARCH_CARD_HEIGHT - 50, 25, WHITE);
}

void DrawArchsToUpgrade(int x, int y, int playerNumber) {

    DrawTexturePro(
        background,
        (Rectangle){0, 0, (float)background.width, (float)background.height},
        (Rectangle){0, 0, (float)screenWidth, (float)screenHeight},
        (Vector2){0, 0},
        0.0f,
        WHITE
    );

    card1.x = x - ARCH_CARD_WIDTH * 1.2;
    card1.y = y;

    card2.x = x + ARCH_CARD_WIDTH * 0.2;
    card2.y = y;

    DrawTextCentered(TextFormat("Jugador %d", playerNumber), x, y - ARCH_CARD_HEIGHT - 50, 30, WHITE);
    DrawTextCentered(TextFormat("Puntos: %d", playerNumber == 1 ? score_player1 : score_player2), x, y - ARCH_CARD_HEIGHT, 20, WHITE);

    switch (playerNumber) {
    case 1:
        if (player1.currentArch != NULL) {
            if (player1.currentArch->previous != NULL) {
                if(score_player1 >= player1.currentArch->previous->cost){
                    if(DrawCard(cardImage, (Rectangle){card1.x, card1.y, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT})){
                        player1.currentArch = player1.currentArch->previous;
                        selection = SELECTION_PLAYER_2;
                    }
                } else {
                    DrawCard(cardImageBloqued, (Rectangle){card1.x, card1.y, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT});
                }
                // Tarjeta 1
                DrawTextureCentered(player1.currentArch->previous->texture, card1.x + card1.width / 2, card1.y +  80, WHITE);
                DrawTextCentered(player1.currentArch->previous->name, card1.x + card1.width / 2, card1.y + ARCH_CARD_HEIGHT - 150, 25, WHITE);
                DrawTextCentered(TextFormat("Daño: %d", player1.currentArch->previous->damage), card1.x + card1.width / 2, card1.y + ARCH_CARD_HEIGHT - 120, 20, LIGHTGRAY);
                DrawTextCentered(TextFormat("Rango: %d", player1.currentArch->previous->range), card1.x + card1.width / 2, card1.y + ARCH_CARD_HEIGHT - 90, 20, LIGHTGRAY);
                DrawTextCentered(TextFormat("m/s: %.1f", player1.currentArch->previous->speed), card1.x + card1.width / 2, card1.y + ARCH_CARD_HEIGHT - 60, 20, LIGHTGRAY);
                DrawTextCentered(TextFormat("Costo: %.1d", player1.currentArch->previous->cost), card1.x + card1.width / 2, card1.y + ARCH_CARD_HEIGHT - 30, 25, WHITE);
            }

            if (player1.currentArch->next != NULL) {
                if(score_player1 >= player1.currentArch->next->cost){
                    if(DrawCard(cardImage, (Rectangle){card2.x, card2.y, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT})){
                        player1.currentArch = player1.currentArch->next;
                        selection = SELECTION_PLAYER_2;
                    }
                } else {
                    DrawCard(cardImageBloqued, (Rectangle){card2.x, card2.y, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT});
                }
                // Tarjeta 2
                DrawTextureCentered(player1.currentArch->next->texture, card2.x + card2.width / 2, card2.y + 80, WHITE);
                DrawTextCentered(player1.currentArch->next->name, card2.x + card2.width / 2, card2.y + ARCH_CARD_HEIGHT - 150, 25, WHITE);
                DrawTextCentered(TextFormat("Daño: %d", player1.currentArch->next->damage), card2.x + card2.width / 2, card2.y + ARCH_CARD_HEIGHT - 120, 20, LIGHTGRAY);
                DrawTextCentered(TextFormat("Rango: %d", player1.currentArch->next->range), card2.x + card2.width / 2, card2.y + ARCH_CARD_HEIGHT - 90, 20, LIGHTGRAY);
                DrawTextCentered(TextFormat("m/s: %.1f", player1.currentArch->next->speed), card2.x + card2.width / 2, card2.y + ARCH_CARD_HEIGHT - 60, 20, LIGHTGRAY);
                DrawTextCentered(TextFormat("Costo: %.1d", player1.currentArch->next->cost), card2.x + card2.width / 2, card2.y + ARCH_CARD_HEIGHT - 30, 25, WHITE);
            }

            if(player1.currentArch->previous == NULL && player1.currentArch->next == NULL){
                selection = SELECTION_PLAYER_2;
            }
        } else {
            selection = SELECTION_PLAYER_2;
        }
        if(score_player1 < player1.currentArch->previous->cost && score_player1 < player1.currentArch->next->cost){
            if(DrawButton("Continuar", btnImage, btnImageHover, (Rectangle){x - rectangleWidth / 2, y + ARCH_CARD_HEIGHT + 30, rectangleWidth, rectangleHeight}, WHITE)){
                selection = SELECTION_PLAYER_2;
            }
        }
        break;
    case 2:
        if (player2.currentArch != NULL) {
            if (player2.currentArch->previous != NULL) {
                if(score_player2 >= player2.currentArch->previous->cost){
                    if(DrawCard(cardImage, (Rectangle){card1.x, card1.y, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT})){
                        player2.currentArch = player2.currentArch->previous;
                        state = STATE_GAME;
                        selection = SELECTION_PLAYER_1;
                    }
                } else {
                    DrawCard(cardImageBloqued, (Rectangle){card1.x, card1.y, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT});
                }
                // Tarjeta 1
                DrawTextureCentered(player2.currentArch->previous->texture, card1.x + card1.width / 2, card1.y +  80, WHITE);
                DrawTextCentered(player2.currentArch->previous->name, card1.x + card1.width / 2, card1.y + ARCH_CARD_HEIGHT - 150, 25, WHITE);
                DrawTextCentered(TextFormat("Daño: %d", player2.currentArch->previous->damage), card1.x + card1.width / 2, card1.y + ARCH_CARD_HEIGHT - 120, 20, LIGHTGRAY);
                DrawTextCentered(TextFormat("Rango: %d", player2.currentArch->previous->range), card1.x + card1.width / 2, card1.y + ARCH_CARD_HEIGHT - 90, 20, LIGHTGRAY);
                DrawTextCentered(TextFormat("m/s: %.1f", player2.currentArch->previous->speed), card1.x + card1.width / 2, card1.y + ARCH_CARD_HEIGHT - 60, 20, LIGHTGRAY);
                DrawTextCentered(TextFormat("Costo: %.1d", player2.currentArch->previous->cost), card1.x + card1.width / 2, card1.y + ARCH_CARD_HEIGHT - 30, 25, WHITE);
            }

            if (player2.currentArch->next != NULL) {
                if(score_player2 >= player2.currentArch->next->cost){
                    if(DrawCard(cardImage, (Rectangle){card2.x, card2.y, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT})){
                        player2.currentArch = player2.currentArch->next;
                        state = STATE_GAME;
                        selection = SELECTION_PLAYER_1;
                    }
                } else {
                    DrawCard(cardImageBloqued, (Rectangle){card2.x, card2.y, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT});
                }
                // Tarjeta 2
                DrawTextureCentered(player2.currentArch->previous->texture, card1.x + card1.width / 2, card1.y +  80, WHITE);
                DrawTextCentered(player2.currentArch->previous->name, card1.x + card1.width / 2, card1.y + ARCH_CARD_HEIGHT - 150, 25, WHITE);
                DrawTextCentered(TextFormat("Daño: %d", player2.currentArch->previous->damage), card1.x + card1.width / 2, card1.y + ARCH_CARD_HEIGHT - 120, 20, LIGHTGRAY);
                DrawTextCentered(TextFormat("Rango: %d", player2.currentArch->previous->range), card1.x + card1.width / 2, card1.y + ARCH_CARD_HEIGHT - 90, 20, LIGHTGRAY);
                DrawTextCentered(TextFormat("m/s: %.1f", player2.currentArch->previous->speed), card1.x + card1.width / 2, card1.y + ARCH_CARD_HEIGHT - 60, 20, LIGHTGRAY);
                DrawTextCentered(TextFormat("Costo: %.1d", player2.currentArch->previous->cost), card1.x + card1.width / 2, card1.y + ARCH_CARD_HEIGHT - 30, 25, WHITE);
            } else {
                state = STATE_GAME;
                selection = SELECTION_PLAYER_1;
            }

            if(player2.currentArch->previous == NULL && player2.currentArch->next == NULL){
                state = STATE_GAME;
                selection = SELECTION_PLAYER_1;
            }
        } else {
            state = STATE_GAME;
            selection = SELECTION_PLAYER_1;
        }
        if(score_player2 < player2.currentArch->previous->cost && score_player2 < player2.currentArch->next->cost){
            if(DrawButton("Continuar", btnImage, btnImageHover, (Rectangle){x - rectangleWidth / 2, y + ARCH_CARD_HEIGHT + 30, rectangleWidth, rectangleHeight}, WHITE)){
                state = STATE_GAME;
                selection = SELECTION_PLAYER_1;
            }
        }
        break;
    default:
        break;
    }
}

Arch *InsertArchNodeInOrder(Arch *root, Arch *newNode) {
    if (!root) return newNode;

    // Usamos una cola simple para BFS
    Arch *queue[128];
    int front = 0, back = 0;
    queue[back++] = root;

    while (front < back) {
        Arch *current = queue[front++];

        if (!current->previous) {
            current->previous = newNode;
            return root;
        } else {
            queue[back++] = current->previous;
        }

        if (!current->next) {
            current->next = newNode;
            return root;
        } else {
            queue[back++] = current->next;
        }
    }

    return root;
}


Arch *LoadArchTreeFromCSV(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error al abrir archivo: %s\n", filename);
        return NULL;
    }

    char line[MAX_LINE_LENGTH];
    Arch *root = NULL;
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        Arch *arch = malloc(sizeof(Arch));
        arch->previous = NULL;
        arch->next = NULL;

        char nameBuffer[64] = {0};
        char textureFile[128] = {0};
        char archFile[128] = {0};

        int matched = sscanf(line, "%d,%63[^,],%f,%d,%f,%d,%127[^,],%127[^,\n]", &arch->index, nameBuffer, &arch->range, &arch->damage, &arch->speed, &arch->cost, textureFile, archFile);

        if (matched != 8) {
            printf("Error parseando línea: %s\n", line);
            free(arch);
            continue;
        }

        arch->name = strdup(nameBuffer);
        if (!arch->name) {
            printf("Error duplicando nombre\n");
            free(arch);
            continue;
        }

        // Cargar textura
        Image img = LoadImage(TextFormat(ASSETS_PATH "%s", textureFile));
        ImageResize(&img, 100, 100);
        arch->texture = LoadTextureFromImage(img);
        UnloadImage(img);

        Image img2 = LoadImage(TextFormat(ASSETS_PATH "%s", archFile));
        ImageResize(&img2, PLAYER_SIZE, PLAYER_SIZE);
        arch->arch = LoadTextureFromImage(img2);
        UnloadImage(img2);

        arch->previous = NULL;
        arch->next = NULL;

        printf("Insertando nodo %d - %s\n", arch->index, arch->name);
        root = InsertArchNodeInOrder(root, arch);
        count++;
    }

    fclose(file);

    if (!root) {
        printf("No se insertaron nodos desde: %s\n", filename);
    } else {
        printf("Se insertaron %d nodos desde: %s\n", count, filename);
    }

    return root;
}


void FreeArchTree(Arch *root) {
    if (!root) return;

    FreeArchTree(root->previous);  // hijo izquierdo
    FreeArchTree(root->next);      // hijo derecho

    UnloadTexture(root->texture);
    free(root->name);
    free(root);
}