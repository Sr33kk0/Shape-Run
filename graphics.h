#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <splashkit.h>
#include <string>
#include "dynarr.h"
#include "types.h"

/**
 * Draws the player on screen
 *
 * @param &p The player data to be updated
 */
void draw_player(player_data &p);

/**
 * Draw the floor of the game
 * When obstacles comes into screen, draw obstacles
 *
 * @param &game The game data to be updated
 */
void draw_game(game_data &game);

/**
 * Procedure to draw the starting screen of the game. Checking user input to start the game.
 *
 * @param game  The game data to be updated.
 */
void draw_starting_screen(game_data &game);

/**
 * Procedure to check for user input to exit from the gmaeplay loop
 *
 * @param game  The game data to be updated
 */
void exit_game(game_data &game);
#endif