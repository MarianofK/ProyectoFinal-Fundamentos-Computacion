#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "raylib.h"
#include "definitions.h"

/// @brief Inicializa la ventana estableciendo su tamaño, título, limitando FPS y redimencion
void InitializeWindow();

/// @brief Efecto hover del mouse sobre algun boton.
/// @param rect Referencia del rectangulo para determinar su colicion.
/// @return Retorna el color que tomara el rectangulo.
Color GetButtonColor(Rectangle rect);

#endif