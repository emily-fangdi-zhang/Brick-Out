/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

// Defines a struct for modeling the ball.

#pragma once

#include "game_config.hxx"

#include <ge211.hxx>

#include <iostream>


/// We will represent positions as GE211 `Posn<float>`s, which we alias
/// with the type name `Position`. This is a struct that could be
/// defined like so:
///
///   struct Position
///   {
///       float x;   // pixel distance from left edge of window
///       float y;   // pixel distance from top edge of window
///   };
using Position = ge211::Posn<float>;


/// We will represent velocities as GE211 `Dims<float>`s, which we alias
/// with the type name `Velocity`. This is a struct that could be
/// defined like so:
///
///   struct Velocity
///   {
///       float width;   // horizontal rate of change (px/s)
///       float height;  // vertical rate of change (px/s)
///   };
using Velocity = ge211::Dims<float>;

/// We will represent blocks (the bricks and the paddle) as GE211
/// `Rect<int>`s, which we alias with the type name `Block`. This is a
/// struct that could be defined like so:
///
///   struct Block
///   {
///       int x;       // x coordinate of left side of rectangle
///       int y;       // y coordinate of top side of rectangle
///       int width;
///       int height;
///   };
using Block = ge211::Rect<int>;


/// This struct is used to represent the state of the ball. In
/// particular, we need to know how big the ball is (radius), whether
/// it's moving or stopped (live), where it is (center), and where it's
/// going (velocity).
///
/// Note that `velocity` is a ge211::Dims<float>, which means it has two
/// `float` member variables, `width` and `height`, which store the *x*
/// and *y* components of the ball's velocity vector expressed in
/// pixels/second. This means that in each "frame", `center` needs to be
/// translated (shifted) by the `velocity` times the amount of time that
/// has passed. A `Dims<float>` may be multiplied by a `double` (or any
/// scalar type) to produce a scaled `Dims<float>` (à la scalar–vector
/// multiplication); and a `Dims<float>` added to a `Posn<float>` yields
/// a translated `Posn<float>`. Thus, a ball `a_ball`'s position may be
/// updated by the statement:
///
///     a_ball.position += dt * a_ball.velocity;
///
struct Ball
{
    //
    // CONSTRUCTOR
    //

    /// Constructs a new ball. It needs to know where the paddle is (so
    /// it can position itself right above it), and the configuration
    /// (which includes the ball's radius and initial velocity). The
    /// ball starts dead---not moving and positioned 1 pixel above the
    /// center of the paddle.
    ///
    /// In addition to constructing the ball in the model in the first
    /// place, this can also be used to reset the ball by creating a new
    /// ball to assign over it:
    ///
    ///     ball = Ball(paddle, config);
    ///
    Ball(Block const& paddle, Game_config const&);

    //
    // MEMBER FUNCTIONS
    //

    /// Returns the position of the top-left corner of the ball's
    /// "bounding box", meaning the smallest rectangle in which is can
    /// be enclosed. This is useful to the UI because sprites are
    /// positioned based on their top-left corners.
    Position top_left() const;

    /// Returns the state of the ball after `dt` seconds have passed,
    /// were it to move freely (without obstacles). Thus, the result is
    /// a new ball just like this one but whose position has been
    /// updated based on its current velocity and the given time
    /// interval `dt`. (This is an application of the equation relating
    /// distance to velocity and time: *Δd = v ⋅ Δt*.)
    ///
    /// This function is useful because the model's algorithm for
    /// collision detection involves speculatively moving the ball and
    /// checking where it would end up, before actually moving it.
    ///
    /// This can also be used to actually move it, via assignment:
    ///
    ///    ball = ball.next();
    ///
    Ball next(double dt) const;

    // These functions all perform collision detection by telling us whether
    // this ball is *past* the given edge.

    /// Determines whether the ball extends past the top edge of the
    /// scene.
    bool hits_top(Game_config const&) const;

    /// Determines whether the ball extends past the bottom edge of the
    /// scene.
    bool hits_bottom(Game_config const&) const;

    /// Determines whether the ball extends past the left or right edge
    /// of the scene.
    bool hits_side(Game_config const&) const;

    /// Determines whether the ball's bounding box intersects with the
    /// given block.
    ///
    /// Intersection between a circle and a rectangle is tricky, so we
    /// will approximate it with the intersection of two rectangles.
    bool hits_block(Block const&) const;

    /// Collision detection between the ball and the whole vector of
    /// bricks. If the ball collides with some brick then that brick is
    /// removed and the function returns true. (The ball may collide
    /// with more than one brick, but the function should return after
    /// the first collision is found.) If there is no collision then the
    /// function returns false.
    bool destroy_brick(std::vector<Block>& bricks) const;

    /// Negates the vertical component of this ball's velocity.
    void reflect_vertical();

    /// Negates the horizontal component of this ball's velocity.
    void reflect_horizontal();

    //
    // MEMBER VARIABLES
    //

    /// The radius of the ball.
    int radius;

    /// The position of the center of the ball.
    Position center;

    /// The velocity of the ball in pixels per tick.
    Velocity velocity;

    /// Whether the ball is moving freely (true) or stuck to the top of
    /// the paddle (false).
    bool live;
};

/// Compares two `Ball`s for equality. This may be useful for testing.
///
/// Two `Ball`s are equal if all their member variables are pairwise
/// equal.
bool
operator==(Ball const&, Ball const&);

/// Inequality for `Ball`s.
bool
operator!=(Ball const&, Ball const&);

/// Stream insertion (printing) for `Ball`. This can make your test
/// results easier to read.
std::ostream&
operator<<(std::ostream&, Ball const&);
