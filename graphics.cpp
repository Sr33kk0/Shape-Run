#include <splashkit.h>
#include <string>

#include "dynarr.h"
#include "types.h"

/**
 * Draws the player on screen
 *
 * @param &p The player data to be updated
 */
void draw_player(player_data &p)
{
    fill_rectangle(color_gray(), p.x, p.y, 50, 50);
}

/**
 * Draw the obstacles of the game
 * When obstacles comes into screen, draw obstacles
 *
 * @param &game The game data to be updated
 */
void draw_game(game_data &game)
{
    clear_screen(color_white());

    draw_player(game.player);
    for (int i = 0; i < game.obstacles->size; i++)
    {
        obstacle &obs = game.obstacles->data[i];
        double screen_x = obs.x - game.camera_x;

        if (screen_x > -obs.width && screen_x < SCREEN_WIDTH)
        {
            switch (obs.type)
            {
                case BLOCKS:
                    fill_rectangle(color_black(), screen_x, obs.y, obs.width, 50);
                    break;
                case SPIKES:
                    fill_triangle(color_red(), screen_x, obs.y, screen_x + 25, obs.y - 50, screen_x + 50, obs.y);
                    break;
                case INVERTED_SPIKES:
                    fill_triangle(color_red(), screen_x, obs.y, screen_x + 25, obs.y + 50, screen_x + 50, obs.y);
                    break;
                case PORTAL_INVERT:
                    fill_rectangle(color_blue(), screen_x, obs.y, 10, 100);
                    break;
                case PORTAL_FLAPPY:
                    fill_rectangle(color_purple(), screen_x, obs.y, 10, 100);
                    break;
                case PORTAL_BASE:
                    fill_rectangle(color_light_gray(), screen_x, obs.y, 10, 100);
                    break;
                default:
                    break;
            }
        }
    }
    refresh_screen(60);
}

/**
 * Procedure to draw the starting screen of the game. Checking user input to start the game.
 *
 * @param game  The game data to be updated.
 */
void draw_starting_screen(game_data &game)
{
    string title = "Shape Run";
    string sub1_title = "Press [SPACE] to start game";
    string sub2_title = "Press [ESCAPE] to go back to menu";
    font menu_font = get_system_font();

    int title_size = 100;
    int sub1_size = 30;
    int sub2_size = 30;

    // Calculation to center the text
    double title_x = (SCREEN_WIDTH / 2) - (text_width(title, menu_font, title_size) / 2);
    double sub1_x = (SCREEN_WIDTH / 2) - (text_width(sub1_title, menu_font, sub1_size) / 2);
    double sub2_x = (SCREEN_WIDTH / 2) - (text_width(sub2_title, menu_font, sub2_size) / 2);

    draw_text(title, color_black(), menu_font, title_size, title_x, 400);
    draw_text(sub1_title, color_black(), menu_font, sub1_size, sub1_x, 600);
    draw_text(sub2_title, color_black(), menu_font, sub2_size, sub2_x, 700);

    if (key_typed(SPACE_KEY))
    {
        game.is_running = true;
    }
}

/**
 * Procedure to check for user input to exit from the gameplay loop
 *
 * @param game  The game data to be updated
 */
void exit_game(game_data &game)
{
    if (key_typed(ESCAPE_KEY))
    {
        game.is_running = false;
    }
}
