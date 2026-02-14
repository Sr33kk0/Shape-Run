#include <splashkit.h>
#include <string>
#include <fstream>

#include "dynarr.h"
#include "types.h"
#include "physics.h"
#include "graphics.h"

using std::ifstream;
using std::to_string;

/**
 * A test function to calculate the stationary state of the transition matrix
 * It calculates the converged probability of states after iterating through multiple walks in the markov chain
 */
void calculate_stationary()
{
    // initialize an initial state to simulate the walk
    double mat[NUM_OF_STATES] = {1, 0, 0, 0, 0, 0, 0};

    double matb[NUM_OF_STATES];
    double sum_i = 0;
    double sum_f = 0;

    // Simulate a random walk from one state to another 1000 times
    // 7x7 Matrix Multiplication
    for (int iter = 0; iter <= 1000; iter++)
    {
        for (int i = 0; i < NUM_OF_STATES; i++)
        {
            for (int j = 0; j < NUM_OF_STATES; j++)
            {
                mat[i] += transition_matrix[j][i] * matb[j];
            }
        }
        for (int i = 0; i < NUM_OF_STATES; i++)
        {
            matb[i] = mat[i];
        }

        for (int i = 0; i < NUM_OF_STATES; i++)
        {
            mat[i] = 0;
        }
    }

    for (int i = 0; i < NUM_OF_STATES; i++)
    {
        write_line("Index " + to_string(i) + " = " + to_string(matb[i]));
    }

    write_line("\nBase Game = " + to_string(matb[0]));
    for (int i = 1; i <= 3; i++)
    {
        sum_i += matb[i];
    }
    write_line("Inverted Gravity = " + to_string(sum_i));
    for (int i = 4; i <= 6; i++)
    {
        sum_f += matb[i];
    }
    write_line("Flappy Gravity = " + to_string(sum_f));
}

/**
 * Function to return the next state utilizing the markov chain
 *
 * @param &game    The game data to be updated
 * @return result   The next game state in struct form
 */
game_state get_next_state(const game_data &game)
{
    double cumulative_probability = 0;
    double roll;
    double next_probabilities[NUM_OF_STATES];
    game_state result;

    roll = rnd(); // random double from 0-1

    // Initialize the probabilities of the next state based on the cufrent state into a 1 dimensional array
    for (int col = 0; col < NUM_OF_STATES; col++)
    {
        next_probabilities[col] = transition_matrix[game.current_state][col];
    }

    // From the results gotten from roll, get the output from the probabilities of the next state
    for (int col = 0; col < NUM_OF_STATES; col++)
    {
        cumulative_probability += next_probabilities[col];
        if (roll < cumulative_probability)
        {
            result = (game_state)col;
            break;
        }
    }
    return result;
}

/**
 * Procedure to load the obstacle data from a text file into the game (includes x offset from chunk loading)
 *
 * @param *obstacles The dynamic array of obstacles to be added into
 * @param filename The file_prefix name of the file_prefix to be read as a string
 */
void load_chunk(dynamic_array<obstacle> *obstacles, string filename, double chunk_end)
{
    ifstream readFile(filename);
    int index;
    double x;
    double y;
    double width;

    while (readFile >> index >> x >> y >> width)
    {
        obstacle obs;
        obs.type = (obstacle_type)index;
        obs.x = x + chunk_end;
        obs.y = y;
        obs.width = width;

        add_to_dynamic_array(obstacles, obs);
    }

    readFile.close();
}

/**
 * Procedure to load the obstacle data from the next chunk into the dynamic array
 *
 * @param &game The game data to be updated
 */
void load_next_chunk(game_data &game)
{
    int num;
    string file_prefix;
    string filename;

    // Loop to delete any obstacles that is passed the map loading
    // By manipulating the size of the dynamic array to remove the elements at the end of the dynamic array
    if (game.obstacles->size > 0)
    {
        int new_size = 0;
        for (int i = 0; i < game.obstacles->size; i++)
        {
            if (game.obstacles->data[i].x + game.obstacles->data[i].width > game.camera_x - 500)
            {
                game.obstacles->data[new_size] = game.obstacles->data[i];
                new_size++;
            }
        }
        game.obstacles->size = new_size;
    }

    switch (game.next_state)
    {
        case BASE:
            file_prefix = "Base";
            break;
        case INVERT_START:
            file_prefix = "InvertStart";
            break;
        case INVERT_MID:
            file_prefix = "InvertMiddle";
            break;
        case INVERT_END:
            file_prefix = "InvertEnd";
            break;
        case FLAPPY_START:
            file_prefix = "FlappyStart";
            break;
        case FLAPPY_MID:
            file_prefix = "FlappyMiddle";
            break;
        case FLAPPY_END:
            file_prefix = "FlappyEnd";
            break;
        default:
            file_prefix = "Not Found";
            break;
    }

    // Choose a random file from filename(num).txt
    num = rnd(1, 3);
    filename = file_prefix + to_string(num) + ".txt";

    load_chunk(game.obstacles, filename, game.chunk_end);

    // Every chunk contains 5000px of obstacle data. Increment this to keep track of the end of the current map.
    game.chunk_end += 5000;

    // Change the current state to the state that is loaded.
    game.current_state = game.next_state;
    game.next_state = get_next_state(game);
}