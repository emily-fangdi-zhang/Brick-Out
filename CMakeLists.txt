cmake_minimum_required(VERSION 3.3)
project(brick_out CXX)
include(.cs211/cmake/CMakeLists.txt)

# Defines a variable to stand for the three .cxx files that implement
# the model.
set(MODEL_SRC
        src/game_config.cxx
        src/ball.cxx
        src/model.cxx)

# Adds a program named `brick_out` built from src/brick_out.cxx and
# the common model files.
add_program(brick_out
        src/brick_out.cxx
        src/controller.cxx
        src/view.cxx
        ${MODEL_SRC})
target_link_libraries(brick_out ge211)

# Adds a test program named `ball_test` built from test/ball_test.cxx
# and the common model files.
add_test_program(ball_test
        test/ball_test.cxx
        ${MODEL_SRC})
target_link_libraries(ball_test ge211)

# Adds a test program named `model_test` built from test/model_test.cxx
# and the common model files.
add_test_program(model_test
        test/model_test.cxx
        ${MODEL_SRC})
target_link_libraries(model_test ge211)

# vim: ft=cmake
