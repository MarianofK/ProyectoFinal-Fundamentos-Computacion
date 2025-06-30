#ifndef GAME_STATE_H
#define GAME_STATE_H

#define rectangleWidth 200.f
#define rectangleHeight 50.f

#define initialWidth 1366
#define initialHeight 768

/// @brief Enumeration para controlar la accion a realizar.
/// | STATE_MENU | STATE_GAME| STATE_MINI_GAME| STATE_SETTINGS | STATE_EXIT |
typedef enum {
  STATE_MENU,
  STATE_MINI_GAME,
  STATE_ARCH_SELECTION,
  STATE_ARCH_UPGRADE,
  STATE_GAME,
  STATE_SETTINGS,
  STATE_EXIT
} GameState;

typedef enum { SELECTION_PLAYER_1, SELECTION_PLAYER_2 } SelectionState;

/// @brief Estado del juego
extern GameState state;

/// @brief Puntuacion de los jugadores
extern int score_player1;
extern int score_player2;

/// @brief Estado de seleccion de los arcos
extern SelectionState selection;

/// @brief Control de dimensiones
extern int screenWidth;
extern int screenHeight;

#endif
