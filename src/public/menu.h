#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include "definitions.h"
#include "functions.h"
#include "player.h"

/// @brief Dibuja el menu centrado con respecto a un punto, mostrando un titulo y las opciones de empezar, ajustes y salir.
/// @param x Posicion del menu en X
/// @param y Posicion del menu en Y
void DrawMenu(int x, int y);

/// @brief Dibuja el menu del final de la partida.
/// @param x Posicion del menu en X
/// @param y Posicion del menu en Y
void DrawEndMenu(int x, int y);

/// @brief Detecta la colision del mouse y actualiza el estado del juego.
/// @return Devuelve un valor del enum GameState.
void UpdateMenu();

/// @brief Actualizar el menu del final del juego
void UpdateEndMenu();

#endif