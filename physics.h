#ifndef PHYSICS_H
#define PHYSICS_H

#include <splashkit.h>
#include <string>

#include "dynarr.h"
#include "types.h"
#include "graphics.h"

/**
 * Lets the player jump with a fixed speed
 *
 * @param &p The player data to be updated
 */
void player_jump(player_data &p);

/**
 * Handles the input of the player
 *
 * @param &p The player data to be updated
 */
void handle_input(player_data &p);

/**
 * Updates player movement. Applies gravity to the player.
 *
 * @param &p The player data to be updated
 */
void update_player(player_data &p);

/**
 * Procedure to restart the game
 * Reseting the player back to original state and camera back to the starting location
 *
 * @param &game The game data to be updated
 */
void restart_game(game_data &game);

/**
 * Procedure to check for every obstacle collision
 * To ensure player does not phase through blocks
 * Player dies if the player comes into contact with the spikes
 *
 *
 * @param &game The game data to be updated
 */
void check_collision(game_data &game);

/**
 * Procedure to restart the game if the player goes out of the screen
 * 
 * 
 * @param &game The game data to be updated
 */
void check_player_bounds(game_data &game);
#endif