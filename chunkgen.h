#ifndef CHUNKGEN_H
#define CHUNKGEN_H

#include <splashkit.h>
#include <string>
#include <fstream>
#include <sstream>

#include "dynarr.h"
#include "types.h"
#include "physics.h"
#include "graphics.h"

using std::ifstream;
using std::stringstream;


/**
 * A test function to calculate the stationary state of the transition matrix
 * It calcualtes the converged probability of states after iterating through multiple walks in the markov chain
 */
void calculate_stationary();

/**
 * Function to return the next state utilizing the markov chain
 * 
 * @param &game    The game data to be updated
 * @return result   The next game state in struct form
 */
game_state get_next_state(game_data &game);

/**
 * Procedure to load the obstacle data from a text file into the game (includes x offset from chunk loading)
 *
 * @param *obstacles The dynamic array of obstacles to be added into
 * @param filename The file_prefix name of the file_prefix to be read as a string
 */
void load_chunk(dynamic_array<obstacle> *obstacles, string filename, double chunk_end);

/**
 * Procedure to load the obstacle data from the next chunk into the dynamic array
 *
 * @param &game The game data to be updated
 */
void load_next_chunk(game_data &game);
#endif