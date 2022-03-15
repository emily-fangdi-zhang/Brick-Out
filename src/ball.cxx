// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "ball.hxx"
#include "game_config.hxx"

// Computes where the ball should be when it's stuck to the paddle:
// centered above it, 1 pixel up.
static Position
above_block(
        Block const& block,
        Game_config const& config)
{
    // Returns a position {x, y}
    return Position (block.top_left().right_by(block.width / 2).up_by(
            1 + config.ball_radius));
}

// It won't compile without this, so you get it for free.
Ball::Ball(Block const& paddle, Game_config const& config)
        : radius(config.ball_radius),
          center(above_block(paddle, config)),
          velocity(Velocity(config.ball_velocity_0)),
          live(false)
{ }

Position
Ball::top_left() const
{
    return Position (center.x - radius, center.y - radius);
}

// The ball hits the bottom of the scene when the y coordinate of its bottom
// exceeds the height of the scene.
bool
Ball::hits_bottom(Game_config const& config) const
{
    return (center.y + radius > config.scene_dims.height);
}

// The ball hits the top when the y coordinate of its top is less than
// 0. (Note that the parameter isn't used.)
bool
Ball::hits_top(Game_config const&) const
{
    return (center.y - radius < 0);
}

// The ball hits a side when the x coordinate of its left side is
// less than 0 or the x coordinate of its right side is greater
// than the width of the scene.
bool
Ball::hits_side(Game_config const& config) const
{
    return (center.x - radius < 0) || (center.x + radius > config
    .scene_dims.width);
}

// Recall that `this` is a `const Ball*`, and you can create a copy of a ball
// with the copy constructor. So to get a new `Ball` to return, you can write
//
//     Ball result(*this);
//
Ball
Ball::next(double dt) const
{
    Ball result(*this);
    result.center = result.center + dt * velocity;
    return result;
}

// As with the edge collision functions, we want to use the ball's
// bounding box. That is, the box whose top is center.y - radius, whose
// left is center.x - radius, whose bottom is center.y + radius, and
// whose right is center.x + radius.
//
// That way, we are checking for the intersection of two rectangles.
//
// One way to think of that is that the rectangles *don't* intersect if
// either of these is true:
//
//  - The right side of one rectangle is to the left of the left side of
//  the other.
//
//  - The bottom of one rectangle is above the top of the other
//
// Otherwise, they do.
//
bool
Ball::hits_block(Block const& block) const
{
    // Right of circle square
    double right_circle = center.x + radius;
    // Right of block
    double right_block = block.x + block.width;

    // Left of circle square
    double left_circle = center.x - radius;
    // Left of block
    double left_block = block.x;

    // Bottom of circle square
    double bottom_circle = center.y + radius;
    // Bottom of block
    double bottom_block = block.y + block.height;

    // Top of the circle square
    double top_circle = center.y - radius;
    // Top of the block
    double top_block = block.y;

    if ((right_circle < left_block) || (left_circle > right_block) ||
    (bottom_circle < top_block) || (bottom_block < top_circle)) {
        return false;

    } else {
        return true;
    }
}

void
Ball::reflect_vertical()
{
    velocity.height *= -1;
}

void
Ball::reflect_horizontal()
{
    velocity.width *= -1;
}

// Once you've written `Ball::hits_block`, finding an element of `bricks`
// that collides with this ball isn't hard (use a for-each loop), but
// how to /remove it once you find it? The more obvious solution may be
// to shift all the elements after it to the left, but that's awkward,
// and there's a cleaner way when the order of the elements of the
// vector doesn't matter:
//
//  1. Replace the hit brick with a copy of the last brick (`bricks.last()`)
//     by assignment. If you want to edit a brick in `bricks`, make sure each
//     brick given by the for-each loop is a reference to the existing brick,
//     not a copy.
//
//  2. Now the brick you didn't want is gone, but you have an extra in the back
//     that duplicates the one you just got rid of, so remove the last brick
//     using pop_back().
//
//  3. Don't keep iterating after a pop_back() or you will go out of
//     bounds, because the loop condition won't adjust to the diminished
//     vector.
//
bool
Ball::destroy_brick(std::vector<Block>& bricks) const
{
    int i = 0;

    for (Block block:bricks) {

        if (hits_block(block)) {
            bricks[i] = bricks.back();
            bricks.pop_back();
            return true;
        }
        ++i;
    }
    return false;
}

bool
operator==(Ball const& a, Ball const& b)
{
    return ((a.radius == b.radius) && (a.velocity == b.velocity) && (a.live ==
    b.live) && (a.radius == b.radius));
}

bool
operator!=(Ball const& a, Ball const& b)
{
    return !(a == b);
}

std::ostream&
operator<<(std::ostream& o, Ball const& ball)
{
    // You may have seen this message when running your tests. It
    // would be more helpful if it showed the contents of each ball,
    // right? So you can make that happen by making this print the
    // contents of the ball (however you like).
    o << "Ball{";
    o << ball.center;
    o << "\n";
    o << ball.velocity;
    o << "\n";
    o << ball.radius;
    return o << "}";
}
