// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "model.hxx"

// Constructs a model from the given `Game_config`. Note
// that the `Game_config` is passed by `const&` but `Model`
// saves its own copy of it.
//
// The `config`, `paddle`, and `ball` member variables need
// to be initialized in an initialization list, not in the body
// of the constructor. And:
//
//   - The paddle needs to be initialized with its top-left
//     at `config.paddle_top_left_0()` and with dimensions
//     `config.paddle_dims`. The *static factory function*
//     `Block::from_top_left(Position, Dimensions)` can be used
//     to construct the `Block` you want.
//
//   - The ball needs to be initialized with the state of the paddle
//     and the game configuration.
//
// Then in the body of the constructor, we need to push_back
// `config.brick_rows * config.brick_cols` into the `bricks`
// vector. In details:
//
//   - Each brick should have dimensions `config.brick_dims()`
//
//   - The first (top-left-most) brick should have its top left
//     at the position {config.side_margin, config.top_margin}.
//
//   - You will need nested loops to create all the bricks in each
//     row and column, but note that the order doesn't matter.
//
//   - The offset between each brick and the next is given by the
//     dimensions of each brick plus `config.brick_spacing`.
//     Or in other words, the x offset is `config.brick_spacing.width
//     + config.brick_dims().width`, and the y offset is the same
//     but with heights.
//
Model::Model(Game_config const& config)
        : config(config),
          paddle(Block::from_top_left(config.paddle_top_left_0(),
                                      config.paddle_dims)),
          ball(paddle, config),
          random_boost_source(-config.max_boost, config.max_boost)
{
    int i = 0;

    while (i < config.brick_rows) {

        int j = 0;

        while (j < config.brick_cols) {

            // x offset
            int x_offset = config.brick_spacing.width +
                    config.brick_dims().width;

            // y offset
            int y_offset = config.brick_spacing.height +
                           config.brick_dims().height;

            int x = config.side_margin + (j * x_offset);
            int y = config.top_margin + (i * y_offset);

            Block brick;
            brick.x = x;
            brick.y = y;

            brick.height = config.brick_dims().height;
            brick.width = config.brick_dims().width;

            bricks.push_back(brick);

            ++j;
        }
        ++i;
    }
}

// Freebie.
void
Model::launch()
{
    ball.live = true;
}

// Warning! Until you write code inside these member functions
// that uses at least one member variable, CLion is likely to
// insist that you can make this function static. Don’t believe
// it! You’ll regret the change if you do once you want to
// access member variables, since a static member function
// doesn't have access to an instance. (You should delete this
// warning after you’ve read it.)
//
// TL;DR: Don't go adding `static` to members.

// If the ball isn't live then you need to make it track the paddle,
// which is best done by constructing a new `Ball` and assigning it to
// `ball`.
void
Model::paddle_to(int x)
{
    paddle.x = x;

    if (ball.live == false) {
        ball = Ball(paddle, config);
    }
}

// The description in model.hxx is pretty detailed. What I will add here:
// You probably just want to call `Ball::next(double) const` twice: once
// speculatively as soon as you know that the ball is live, and again at the
// end, storing the result back to the ball that time.
void
Model::on_frame(double dt)
{
    if (ball.live){

        Ball new_ball = ball.next(dt);

        // If the next position of the ball is off the bottom of the
        // screen (according to Ball::hits_bottom(Game_config const&)),
        // resets the ball to dead (which implies placing it back
        // above the paddle) and returns
        if (new_ball.hits_bottom(config)) {
            ball = Ball(paddle, config);
            return;

        } else if (new_ball.hits_top(config) && new_ball.hits_side(config)) {
            ball.reflect_horizontal();
            ball.reflect_vertical();

        // If the next position of the ball would be off the top of
        // the screen, reflects the velocity of the ball vertically
        } else if (new_ball.hits_top(config)) {
            ball.reflect_vertical();

        // If the next position of the ball would be off one side of
        // the screen, reflects the velocity of the ball horizontally
        } else if (new_ball.hits_side(config)) {
            ball.reflect_horizontal();

        // If the next position of the ball hits the paddle then it
        // reflects vertical component of the ball's velocity
        } else if (new_ball.hits_block(paddle)) {
            ball.reflect_vertical();

       // If the next position of the ball destroys a brick via
       // Ball::destroy_bricks(std::vector<Block>&) then it reflects
       // the ball vertically (regardless of which edge of the brick it
       //  strikes [1]) and adds to its horizontal velocity a random
       //  boost [2] chosen from the interval [-config.max_boost,
       // config.max_boost].
        } else if (new_ball.destroy_brick(bricks)) {
            ball.reflect_vertical();
            ball.velocity.width = random_boost_source.next() + (ball.velocity
                    .width);
        }

        // If the ball moves without obstacles
        ball = ball.next(dt);
    }
}