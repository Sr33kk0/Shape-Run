#include <splashkit.h>
#include <string>

#include "dynarr.h"
#include "types.h"
#include "physics.h"
#include "graphics.h"
#include "chunkgen.h"

int main()
{
    open_window("Shape Run", SCREEN_WIDTH, SCREEN_HEIGHT);
    game_data game;
    game.camera_x = 0;
    game.game_speed = 12.5;
    game.current_state = BASE;
    game.next_state = BASE;
    game.is_running = false;

    game.player.x = 500;
    game.player.y = 450;
    game.player.velocity_y = 0;
    game.player.is_dead = false;
    game.player.on_ground = true;
    game.player.gravity = 3.5;
    game.player.is_flappy = false;

    // Create a starting platform at the start of the game
    game.obstacles = create_dynamic_array<obstacle>();
    obstacle start = {BLOCKS, 0, 500, 1000};
    add_to_dynamic_array(game.obstacles, start);
    game.chunk_end = 1000;
    load_next_chunk(game);

    while (!quit_requested())
    {
        clear_screen(color_white());
        handle_input(game.player);
        update_player(game.player);

        draw_starting_screen(game);
        exit_game(game);

        if (game.is_running)
        {
            // Side-scrolling mechanics
            game.camera_x += game.game_speed;

            // Loads the next chunk if the camera is almost at the end of the map
            if (game.camera_x + SCREEN_WIDTH > game.chunk_end - 3000)
            {
                load_next_chunk(game);
            }
            draw_game(game);
            check_collision(game);
            check_player_bounds(game);
        }

        refresh_screen(60);
        process_events();
    }

    free_dynamic_array(game.obstacles);
    return 0;
}