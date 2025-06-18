#ifndef GAME_STATE_H
#define GAME_STATE_H

#define rectangleWidth 200.f
#define rectangleHeight 50.f

#define initialWidth 1366
#define initialHeight 768

/// @brief Enumeration para controlar la accion a realizar.
/// | STATE_MENU | STATE_GAME| STATE_SETTINGS | STATE_EXIT |
typedef enum {
    STATE_MENU,
    STATE_GAME,
    STATE_SETTINGS,
    STATE_EXIT
} GameState;

/// @brief Control de dimensiones
extern int screenWidth;
extern int screenHeight;

#endif
