#ifndef SETTINGS_H
#define SETTINGS_H

#include "raylib.h"
#include "definitions.h"
#include "functions.h"

/// @brief Inicializa el volumen global
void InitSettings();

/// @brief Dibuja el slider para controlar el volumen
/// @param x Posicion en X
/// @param y Posicion en Y
void DrawSettings(int x, int y);

/// @brief Actualiza el nuevo volumen
void UpdateSettings();

/// @brief Comprueba si se pulso algun boton
void BackToMenu();

/// @brief Obtiene el volumen actual
/// @return Retorna el valor del volumen entre (0 - 1)
float GetVolume();

#endif