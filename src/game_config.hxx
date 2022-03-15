/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

// Defines a struct to hold configuration parameters. You should try different
// values to ensure that your model and UI adjust appropriately. You can do this
// by creating an instance and then assigning its parameters before constructing
// a `Model`:
//
//     Game_config config;
//     config.brick_cols = 15;
//     config.ball_radius *= 2;
//     Model model(config);
//

#pragma once

#include <ge211.hxx>


struct Game_config
{
    // Constructs an instance with the default parameters.
    Game_config();

    // The dimensions of the whole window:
    ge211::Dims<int> scene_dims;

    // The dimensions of the paddle (the block at the bottom):
    ge211::Dims<int> paddle_dims;

    // Number of columns of bricks:
    int brick_cols;

    // Number of rows of bricks:
    int brick_rows;

    // The number of pixels of space between each column and row of
    // bricks:
    ge211::Dims<int> brick_spacing;

    // The radius of the ball:
    int ball_radius;

    // The ball's initial velocity {width, height}:
    ge211::Dims<int> ball_velocity_0;

    // The maximum amount that bouncing off the paddle boosts the ball's x
    // velocity component:
    int max_boost;

    // Number of pixels from top of screen to top of brick formation:
    int top_margin;

    // Number of pixels from sides of screen to sides of brick formation:
    int side_margin;

    // Number of pixels from *top* of screen to *bottom* of brick formation.
    int brick_depth;

    // Number of pixels from bottom of screen to bottom of paddle.
    int bottom_margin;

    // The initial state of the paddle. This is a member function because
    // it's computed from the other properties.
    ge211::Posn<int> paddle_top_left_0() const;

    // The dimensions of each brick. Also computed from the other properties.
    //
    // PRECONDITIONS (asserted):
    //  - brick_cols > 0
    //  - brick_rows > 0
    ge211::Dims<int> brick_dims() const;
};

