/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

#include "game_config.hxx"

// This is the default (and only) constructor for `Game_config`. It
// determines all the default values of all the member variables.
Game_config::Game_config()
        : scene_dims {1024, 768},
          paddle_dims {100, 20},
          brick_cols {10},
          brick_rows {10},
          brick_spacing {10, 5},
          ball_radius {5},
          ball_velocity_0 {150, -600},
          max_boost {20},
          top_margin {100},
          side_margin {170},
          brick_depth {300},
          bottom_margin {50}
{ }

ge211::Posn<int>
Game_config::paddle_top_left_0() const
{
    ge211::Posn<int> result(scene_dims);
    result.x /= 2;
    return result.up_by(bottom_margin + paddle_dims.height);
}

// Computes how large each brick can be (in a given dimension), given the
// total number of pixels available in that dimension, the number of bricks
// in that dimensions, and the number of space pixels to leave in between.
//
// PRECONDITION: divisor > 0
static int
div_w_spacing(int total, int divisor, int space)
{
    if (divisor < 0) {
        throw ge211::Client_logic_error("need at least 1 row & 1 column");
    }

    return (total - (divisor - 1) * space) / divisor;
}

// Computes the dimensions of each brick from the other parameters.
ge211::Dims<int>
Game_config::brick_dims() const
{
    int field_width = scene_dims.width - 2 * side_margin;
    int field_height = brick_depth - top_margin;
    int width = div_w_spacing(field_width, brick_cols, brick_spacing.width);
    int height = div_w_spacing(field_height, brick_rows, brick_spacing.height);
    return {width, height};
}
