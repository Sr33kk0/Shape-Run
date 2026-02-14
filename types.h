#ifndef TYPES_H
#define TYPES_H

#include <splashkit.h>
#include <string>

#include "dynarr.h"

const double SCREEN_HEIGHT = 1080;
const double SCREEN_WIDTH = 1920;
const int NUM_OF_STATES = 7;

struct player_data
{
    double x;
    double y;
    double gravity;
    double velocity_y;
    bool is_dead;
    bool is_flappy;
    bool on_ground;
};

enum obstacle_type
{
    BLOCKS = 0,
    SPIKES,
    INVERTED_SPIKES,
    PORTAL_INVERT,
    PORTAL_FLAPPY,
    PORTAL_BASE
};

enum game_state
{
    BASE,
    INVERT_START,
    INVERT_MID,
    INVERT_END,
    FLAPPY_START,
    FLAPPY_MID,
    FLAPPY_END
};

struct obstacle
{
    obstacle_type type;
    double x;
    double y;
    double width;
};

struct game_data
{
    double camera_x;
    double chunk_end;
    double game_speed;
    player_data player;
    game_state current_state;
    game_state next_state;
    dynamic_array<obstacle> *obstacles;
    bool is_running;
};

/**
 * The transition matrix of the markov chain.
 * Each row represents the probabilities of the next state based on the current state
 *
 * extern: To clarify that the array is being declared in another place
 */
extern double transition_matrix[7][7];
#endif