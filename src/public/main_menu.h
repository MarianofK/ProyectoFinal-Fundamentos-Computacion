#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "raylib.h"
#include "definitions.h"
#include "functions.h"

/// @brief Dibuja el menu centrado con respecto a un punto, mostrando un titulo y las opciones de empezar, ajustes y salir.
/// @param x Posicion del menu en X
/// @param y Posicion del menu en Y
void DrawMenu(int x, int y);

/// @brief Detecta la colision del mouse y actualiza el estado del juego.
/// @return Devuelve un valor del enum GameState.
GameState UpdateMenu();

#endif