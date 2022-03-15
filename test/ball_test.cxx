#include "ball.hxx"
#include <catch.hxx>

Block const The_Paddle {100, 400, 100, 20};

TEST_CASE("Ball::Ball")
{
    Game_config config;
    Ball ball(The_Paddle, config);

    CHECK(ball.center.x == 150);
    CHECK(ball.center.y == 394);
}

TEST_CASE("Ball::hits_side")
{
    Game_config config;
    Ball ball(The_Paddle, config);

    CHECK_FALSE(ball.hits_side(config));
    ball.center.x = 1;
    CHECK(ball.hits_side(config));
    ball.center.x = config.scene_dims.width - 1;
    CHECK(ball.hits_side(config));
    ball.center.x = config.scene_dims.width / 2;
    CHECK_FALSE(ball.hits_side(config));
}

TEST_CASE("Ball::hits_top")
{
    Game_config config;
    Ball ball(The_Paddle, config);

    CHECK_FALSE(ball.hits_top(config));
    ball.center.y = 1;
    CHECK(ball.hits_top(config));

    ball.center.y = config.scene_dims.height - 1;
    CHECK_FALSE(ball.hits_top(config));

    ball.center.y = config.scene_dims.height / 2;
    CHECK_FALSE(ball.hits_top(config));
}
