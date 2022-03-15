/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

// The model tracks the logical state of the game, independent of the
// presentation and control. In particular, it keeps track of:
//
//  - the game configuration (the sizes of things such as bricks, the paddle,
//    and the screen),
//
//  - the locations and sizes of all the bricks,
//
//  - the location and size of the paddle (the thing at the bottom that you
//    control), and
//
//  - the state of the ball, including its location and velocity (grouped in
//    the `Ball` struct).
//
// It also provides three member functions to help the UI in updating it.
//

#pragma once

#include "ball.hxx"
#include "game_config.hxx"
#include <vector>


// The logical state of the game.
struct Model
{
    ///
    /// CONSTRUCTOR
    ///

    // Constructs a model from a game configuration.
    //
    // The `= Game_config()` syntax makes the argument optional, in which case
    // it defaults to the default `Game_config`. That is, you can explicitly
    // create a `Game_config` to pass the `Model` constructor like so:
    //
    //     Game_config config;
    //     config.ball_radius = 2;
    //     Model model(config);
    //
    // Or you can omit the constructor argument, in which case you get
    // the default `Game_config` (as defined in game_config.cpp):
    //
    //     Model model;
    //
    // The word `explicit` means that this constructor doesn't define an
    // implicit conversion whereby C++ would automatically convert
    // `Game_config`s into `Model`s if needed. You don't want that.
    explicit Model(Game_config const& config = Game_config());

    ///
    /// MEMBER FUNCTIONS
    ///

    // Makes the ball live if it isn't already.
    void launch();

    // Changes the x coordinate of the (left edge of the) paddle to the
    // given x. Then, only if the ball is dead, updates the ball to
    // follow the paddle.
    void paddle_to(int x);

    // Updates the state of the game for one frame (usually 1/60 s).
    //
    // If the ball is dead then nothing happens. Otherwise there are
    // several possible cases, depending on the speculative next
    // position of the ball according to `Ball::next() const`. In
    // particular:
    //
    //  1. If the next position of the ball is off the bottom of the
    //     screen (according to Ball::hits_bottom(Game_config const&)),
    //     resets the ball to dead (which implies placing it back
    //     above the paddle) and returns.
    //
    //  2. If the next position of the ball would be off the top of
    //     the screen, reflects the velocity of the ball vertically.
    //
    //  3. If the next position of the ball would be off one side of
    //     the screen, reflects the velocity of the ball horizontally.
    //
    // (Note that cases 2 and 3 can both happen at the same time!)
    //
    //  4. If the next position of the ball hits the paddle then it
    //     reflects vertical component of the ball's velocity.
    //
    //  5. If the next position of the ball destroys a brick (via
    //     Ball::destroy_bricks(std::vector<Block>&) then it reflects
    //     the ball vertically (regardless of which edge of the brick it
    //     strikes [1]) and adds to its horizontal velocity a random
    //     boost [2] chosen from the interval [-config.max_boost,
    //     config.max_boost].
    //
    // In all cases where the ball is still live (2–5), we then update
    // the ball to its next position for real.
    //
    // [1] Yes, this is weird physics.
    //
    // [2] This is the only way that the velocity of the ball varies in
    //     anything other than sign.
    //
    void on_frame(double dt);

    ///
    /// MEMBER VARIABLES
    ///

    // The configuration parameters of the model. See game_config.hxx for a
    // description of what this determines. Models can be constructed with
    // different configurations, but the configuration never changes on an
    // existing model.
    Game_config const config;

    // All of the bricks, in no particular order. `Block` is a type
    // alias for `ge211::Rect<float>`, which means it gives both the
    // position of the top-left corner of each brick and the dimensions.
    std::vector<Block> bricks;

    // The position and dimensions of the paddle.
    Block paddle;

    // The state of the ball. Much of the model's business actually
    // happens in there, so see ball.hxx for that.
    Ball ball;

    // A source of random “boost” values.
    ge211::Random_source<float> random_boost_source;
};

