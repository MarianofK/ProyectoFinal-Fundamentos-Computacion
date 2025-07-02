#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include "definitions.h"
#include "functions.h"
#include "player.h"

/// @brief Imagen de fondo del menu
extern Texture2D backgroundMenu;

/// @brief Imagen de fondo
extern Texture2D background;

/// @brief Imagen de boton pulsado
extern Texture2D btnImageHover;

/// @brief Imagen normal del boton
extern Texture2D btnImage;

/// @brief Inicializa los recursos para el menu
void InitMenu();

/// @brief Dibuja el menu centrado con respecto a un punto, mostrando un titulo y las opciones de empezar, ajustes y salir.
/// @param x Posicion del menu en X
/// @param y Posicion del menu en Y
void DrawMenu(int x, int y);

/// @brief Dibuja el menu del final de la partida.
/// @param x Posicion del menu en X
/// @param y Posicion del menu en Y
void DrawEndMenu(int x, int y);

#endif