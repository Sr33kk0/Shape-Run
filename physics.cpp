#include <splashkit.h>
#include <string>

#include "dynarr.h"
#include "types.h"
#include "graphics.h"
#include "chunkgen.h"

/**
 * Lets the player jump with a fixed speed
 *
 * @param &p The player data to be updated
 */
void player_jump(player_data &p)
{
    if (!p.is_flappy)
    {
        if (p.on_ground)
        {
            if (p.gravity > 0)
            {
                p.velocity_y = -30;
            }
            else
            {
                p.velocity_y = 30;
            }
            p.on_ground = false;
        }
    }

    // Flappy Birds Jump Mechanic: Allowing player to jump without being on the ground
    else
    {
        p.velocity_y = -30;
    }
}

/**
 * Updates player movement. Applies gravity to the player.
 *
 * @param &p The player data to be updated
 */
void update_player(player_data &p)
{
    p.velocity_y += p.gravity;
    p.y += p.velocity_y;
}

/**
 * Handles the input of the player
 *
 * @param &p The player data to be updated
 */
void handle_input(player_data &p)
{
    if (key_down(SPACE_KEY))
    {
        player_jump(p);
    }
}

/**
 * Procedure to restart the game
 * Reseting the player back to original state and camera back to the starting location
 *
 * @param &game The game data to be updated
 */
void restart_game(game_data &game)
{
    game.camera_x = 0;
    game.game_speed = 12.5;
    game.current_state = BASE;
    game.next_state = BASE;
    game.chunk_end = 0;

    game.player.y = 450;
    game.player.velocity_y = 0;
    game.player.is_dead = false;
    game.player.x = 500;
    game.player.is_flappy = false;
    game.player.gravity = 3.5;

    game.obstacles->size = 0;
    obstacle start = {BLOCKS, 0, 500, 1000};
    add_to_dynamic_array(game.obstacles, start);
    game.chunk_end = 1000;
    load_next_chunk(game);
}

/**
 * Procedure to check for every obstacle collision
 * To ensure player does not phase through blocks
 * Player dies if the player comes into contact with the spikes
 *
 *
 * @param &game The game data to be updated
 */
void check_collision(game_data &game)
{
    rectangle player_rectangle = rectangle_from(game.player.x, game.player.y, 50, 50);

    for (int i = 0; i < game.obstacles->size; i++)
    {
        obstacle &obs = game.obstacles->data[i];
        double screen_x = obs.x - game.camera_x;

        if (obs.type == BLOCKS)
        {
            rectangle block_rectangle = rectangle_from(screen_x, obs.y, obs.width, 50);

            if (rectangles_intersect(player_rectangle, block_rectangle))
            {
                // Normal Gravity
                if (game.player.gravity > 0 && game.player.velocity_y > 0 && (game.player.y - 40) <= obs.y && !game.player.is_flappy)
                {
                    game.player.y = obs.y - 50;
                    game.player.velocity_y = 0;
                    game.player.on_ground = true;
                }

                // Inverse Gravity
                else if (game.player.gravity < 0 && game.player.velocity_y < 0 && game.player.y >= (obs.y + 10) && !game.player.is_flappy)
                {
                    game.player.y = obs.y + 50;
                    game.player.velocity_y = 0;
                    game.player.on_ground = true;
                }

                // Side + Under Collision or Flappy Mode (Any Block Collision)
                else
                {
                    game.player.is_dead = true;
                    restart_game(game);
                }
            }
        }

        if (obs.type == SPIKES)
        {
            triangle spike_triangle = triangle_from(screen_x, obs.y, screen_x + 25, obs.y - 50, screen_x + 50, obs.y);

            if (triangle_rectangle_intersect(spike_triangle, player_rectangle))
            {
                game.player.is_dead = true;
                restart_game(game);
                return;
            }
        }

        if (obs.type == INVERTED_SPIKES)
        {
            triangle spike_triangle = triangle_from(screen_x, obs.y, screen_x + 25, obs.y + 50, screen_x + 50, obs.y);

            if (triangle_rectangle_intersect(spike_triangle, player_rectangle))
            {
                game.player.is_dead = true;
                restart_game(game);
                return;
            }
        }

        if (obs.type == PORTAL_INVERT)
        {
            rectangle portal_gravity_rectangle = rectangle_from(screen_x, obs.y, 10, 100);

            if (rectangles_intersect(player_rectangle, portal_gravity_rectangle))
            {
                game.player.gravity = -3.5;
            }
        }

        if (obs.type == PORTAL_FLAPPY)
        {
            rectangle portal_flappy_rectangle = rectangle_from(screen_x, obs.y, 10, 100);

            if (rectangles_intersect(player_rectangle, portal_flappy_rectangle))
            {
                if (game.player.gravity < 0)
                {
                    game.player.gravity = 3.5;
                }
                game.player.is_flappy = true;
            }
        }

        if (obs.type == PORTAL_BASE)
        {
            rectangle portal_base_rectangle = rectangle_from(screen_x, obs.y, 10, 100);

            if (rectangles_intersect(player_rectangle, portal_base_rectangle))
            {
                game.player.is_flappy = false;
                game.player.gravity = 3.5;
            }
        }
    }
}

/**
 * Procedure to restart the game if the player goes out of the screen
 *
 * @param &game The game data to be updated
 */
void check_player_bounds(game_data &game)
{
    if (game.player.y > SCREEN_HEIGHT || game.player.y < 0)
    {
        restart_game(game);
    }
}
