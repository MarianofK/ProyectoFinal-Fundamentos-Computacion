#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "raylib.h"
#include "definitions.h"

/// @brief Inicializa la ventana estableciendo su tamaño, título, limitando FPS y redimencion
void InitializeWindow();

/// @brief Controlador de sonido del juego
/// @param path Ruta del recurso de audio
void PlayLevelMusic(const char *path);

/// @brief Dibuja el texto centrado al punto
/// @param text char[] a mostrar
/// @param x Posicion en X
/// @param y Posicion en Y
/// @param fontSize Tamaño de la fuente
/// @param color Color del texto
void DrawTextCentered(const char *text, int x, int y, int fontSize, Color color);

/// @brief Dibuja una textura centrada al punto
/// @param texture Textura a dibujar
/// @param centerX Posicion X
/// @param centerY Posicion Y
/// @param tint Color
void DrawTextureCentered(Texture2D texture, int centerX, int centerY, Color tint);

/// @brief Dibuja un boton con texto
/// @param text Texto a mostrar
/// @param imgNormal Imagen normal
/// @param imgHover Imagen con efecto
/// @param bounds Area del boton
/// @param color Color de texto
/// @return Devuelve un bool que indica si fue presionado
bool DrawButton(char *text, Texture2D imgNormal, Texture2D imgHover, Rectangle bounds, Color color);

/// @brief Dibuja una tarjeta
/// @param normal Textura a mostrar
/// @param bounds Dimensiones
/// @return Retorna si fue pulsada o no
bool DrawCard(Texture2D normal, Rectangle bounds);

#endif