#include "arch.h"
#include "definitions.h"
#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Arch *arch1 = NULL, *arch2 = NULL, *arch3 = NULL;

Rectangle card1 = {0, 0, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT};
Rectangle card2 = {0, 0, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT};
Rectangle card3 = {0, 0, ARCH_CARD_WIDTH, ARCH_CARD_HEIGHT};

Color selectedColor = (Color){0, 0, 0, 10};

bool bSelected = false;

void InitArchs() {
    arch1 = LoadArchTreeFromCSV(ASSETS_PATH "/data/arch_tree1.csv");
    arch2 = LoadArchTreeFromCSV(ASSETS_PATH "/data/arch_tree2.csv");
    arch3 = LoadArchTreeFromCSV(ASSETS_PATH "/data/arch_tree3.csv");
}

void DrawArch(Arch *arch, Vector2 playerPosition, Vector2 playerDirection) {
    float angle = atan2f(playerDirection.y, playerDirection.x) * RAD2DEG;

    DrawTexturePro(arch->arch,
        (Rectangle){0, 0, arch->arch.width, arch->arch.height},
        (Rectangle){playerPosition.x, playerPosition.y + 10,
                    arch->arch.width, arch->arch.height},
        (Vector2){arch->arch.width / 2, arch->arch.height / 2},
        angle, WHITE);
}

void DrawSelectionArch(int x, int y, int playerNumber) {

    if(bSelected) {
        state = STATE_ARCH_UPGRADE;
        selection = SELECTION_PLAYER_1;
    }

    Vector2 mouse = GetMousePosition();

    card1.x = x - ARCH_CARD_WIDTH * 1.6;
    card1.y = y;

    card2.x = x - ARCH_CARD_WIDTH * 0.5;
    card2.y = y;

    card3.x = x + ARCH_CARD_WIDTH * 0.6;
    card3.y = y;

    if (player1.currentArch == arch1 || player2.currentArch == arch1) {
        DrawRectangleRec(card1, selectedColor);
    } else {
        DrawRectangleRec(card1, LIGHTGRAY);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(mouse, card1)) {
            if (playerNumber == 1) {
                player1.currentArch = arch1;
                selection = SELECTION_PLAYER_2;
            } else {
                player2.currentArch = arch1;
                bSelected = true;
                state = STATE_ARCH_UPGRADE;
                selection = SELECTION_PLAYER_1;
            }
        }
    }
    DrawTexture(arch1->texture, card1.x, card1.y, WHITE);
    DrawText(arch1->name, card1.x + 45, card1.y + ARCH_CARD_HEIGHT - 30, 20, BLACK);

    if (player1.currentArch == arch2 || player2.currentArch == arch2) {
        DrawRectangleRec(card2, selectedColor);
    } else {
        DrawRectangleRec(card2, LIGHTGRAY);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(mouse, card2)) {
            if (playerNumber == 1) {
                player1.currentArch = arch2;
                selection = SELECTION_PLAYER_2;
            } else {
                player2.currentArch = arch2;
                bSelected = true;
                state = STATE_ARCH_UPGRADE;
                selection = SELECTION_PLAYER_1;
            }
        }
    }
    DrawTexture(arch2->texture, card2.x, card2.y, WHITE);
    DrawText(arch2->name, card2.x + 25, card2.y + ARCH_CARD_HEIGHT - 30, 20, BLACK);

    if (player1.currentArch == arch3 || player2.currentArch == arch3) {
        DrawRectangleRec(card3, selectedColor);
    } else {
        DrawRectangleRec(card3, LIGHTGRAY);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(mouse, card3)) {
            if (playerNumber == 1) {
                player1.currentArch = arch3;
                selection = SELECTION_PLAYER_2;
            } else {
                player2.currentArch = arch3;
                bSelected = true;
                state = STATE_ARCH_UPGRADE;
                selection = SELECTION_PLAYER_1;
            }
        }
    }
    DrawTexture(arch3->texture, card3.x, card3.y, WHITE);
    DrawText(arch3->name, card3.x + 35, card3.y + ARCH_CARD_HEIGHT - 30, 20, BLACK);
}

void DrawArchsToUpgrade(int x, int y, int playerNumber) {
    Vector2 mouse = GetMousePosition();

    card1.x = x - ARCH_CARD_WIDTH * 1.2;
    card1.y = y;
    DrawRectangleRec(card1, LIGHTGRAY);

    card2.x = x + ARCH_CARD_WIDTH * 0.2;
    card2.y = y;
    DrawRectangleRec(card2, LIGHTGRAY);

    if (player1.currentArch == NULL) printf("player1.currentArch es NULL\n");
    if (player2.currentArch == NULL) printf("player2.currentArch es NULL\n");

    switch (playerNumber) {
    case 1:
        if (player1.currentArch != NULL) {
            if (player1.currentArch->previous != NULL) {
                DrawTexture(player1.currentArch->previous->texture, card1.x, card1.y, WHITE);
                int fontSize = 20;
                const char *text = player1.currentArch->previous->name;
                int textWidth = MeasureText(text, fontSize);
                float textX = card1.x + (card1.width - textWidth) / 2.0f;
                float textY = card1.y + ARCH_CARD_HEIGHT - 30;
                DrawText(text, textX, textY, fontSize, BLACK);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                    CheckCollisionPointRec(mouse, card1)) {
                    player1.currentArch = player1.currentArch->previous;
                    selection = SELECTION_PLAYER_2;
                }
            } else {
                selection = SELECTION_PLAYER_2;
            }

            if (player1.currentArch->next != NULL) {
                DrawTexture(player1.currentArch->next->texture, card2.x, card2.y, WHITE);
                int fontSize = 20;
                const char *text = player1.currentArch->next->name;
                int textWidth = MeasureText(text, fontSize);
                float textX = card2.x + (card2.width - textWidth) / 2.0f;
                float textY = card2.y + ARCH_CARD_HEIGHT - 30;
                DrawText(text, textX, textY, fontSize, BLACK);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                    CheckCollisionPointRec(mouse, card2)) {
                    player1.currentArch = player1.currentArch->next;
                    selection = SELECTION_PLAYER_2;
                }
            } else {
                selection = SELECTION_PLAYER_2;
            }
        } else {
            selection = SELECTION_PLAYER_2;
        }
    break;

    case 2:
        if (player2.currentArch != NULL) {
            if (player2.currentArch->previous != NULL) {
                DrawTexture(player2.currentArch->previous->texture, card1.x, card1.y, WHITE);
                int fontSize = 20;
                const char *text = player2.currentArch->previous->name;
                int textWidth = MeasureText(text, fontSize);
                float textX = card1.x + (card1.width - textWidth) / 2.0f;
                float textY = card1.y + ARCH_CARD_HEIGHT - 30;
                DrawText(text, textX, textY, fontSize, BLACK);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                    CheckCollisionPointRec(mouse, card1)) {
                    player2.currentArch = player2.currentArch->previous;
                    state = STATE_GAME;
                    selection = SELECTION_PLAYER_1;
                }
            } else {
                state = STATE_GAME;
                selection = SELECTION_PLAYER_1;
            }

            if (player2.currentArch->next != NULL) {
                DrawTexture(player2.currentArch->next->texture, card2.x, card2.y, WHITE);
                int fontSize = 20;
                const char *text = player2.currentArch->next->name;
                int textWidth = MeasureText(text, fontSize);
                float textX = card2.x + (card2.width - textWidth) / 2.0f;
                float textY = card2.y + ARCH_CARD_HEIGHT - 30;
                DrawText(text, textX, textY, fontSize, BLACK);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                    CheckCollisionPointRec(mouse, card2)) {
                    player2.currentArch = player2.currentArch->next;
                    state = STATE_GAME;
                    selection = SELECTION_PLAYER_1;
                }
            } else {
                state = STATE_GAME;
                selection = SELECTION_PLAYER_1;
            }
        } else {
            state = STATE_GAME;
            selection = SELECTION_PLAYER_1;
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

        int matched = sscanf(line, "%d,%63[^,],%f,%d,%d,%127[^,],%127[^,\n]", &arch->index, nameBuffer, &arch->cadence, &arch->damage, &arch->cost, textureFile, archFile);

        if (matched != 7) {
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
        ImageResize(&img, 150, 150);
        arch->texture = LoadTextureFromImage(img);
        UnloadImage(img);

        Image img2 = LoadImage(TextFormat(ASSETS_PATH "%s", archFile));
        ImageResize(&img2, PLAYER_SIZE, PLAYER_SIZE);
        arch->arch = LoadTextureFromImage(img2);
        UnloadImage(img2);

        printf("Insertando nodo %d - %s\n", arch->index, arch->name);
        root = InsertArchNodeInOrder(root, arch);
        count++;

        arch->previous = NULL;
        arch->next = NULL;
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