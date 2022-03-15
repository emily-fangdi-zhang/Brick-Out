// IT MIGHT BE OKAY TO MODIFY THIS FILE, BUT YOU PROBABLY DON'T
// WANT TO.
//
// Defines the structure and resources of the user interface.
//

#pragma once

#include <ge211.hxx>

// Forward declaration of our model struct. This lets us use references
// to Model in this file even though the definition isn’t visible. (Just
// like in C.)
struct Model;

struct View
{
    //
    // CONSTRUCTOR
    //

    /// Constructs a `View` given a const reference to the model that
    /// stores the actual state of the game. This lets the view observe
    /// the model’s state but not modify it.
    ///
    /// The word `explicit` means that this constructor doesn't define
    /// an implicit conversion whereby you could pass a `Model` to a
    /// function that expects a `View` and have it work.
    explicit View(Model const&);

    //
    // MEMBER FUNCTIONS
    //

    /// Returns the size of the window as given by `config.scene_dims`.
    ge211::Dims<int> initial_window_dimensions() const;

    /// Renders all the game entities to the screen. In particular,
    /// `ball_sprite` is placed at the ball's bounding box's top-left,
    /// `paddle_sprite` is placed where the model says the paddle is,
    /// and `brick_sprite` is placed for each brick in `model.bricks`.
    void draw(ge211::Sprite_set&);


    //
    // MEMBER VARIABLES
    //

    /// This is a reference to the model. It means that the view doesn't
    /// own the model but has access to it. Thus, the client of the view
    /// (controller.cxx) must have or create a `Model` first and then
    /// pass that by reference to the `View` constructor.
    Model const& model;

    // These three definitions hold the sprites that we need to
    // display the circle, the paddle, and the bricks to the screen.
    // They’re initialized in View’s constructor (in view.cxx, see
    // View::View(Model const&))
    ge211::Circle_sprite const ball_sprite;
    ge211::Rectangle_sprite const paddle_sprite;
    ge211::Rectangle_sprite const brick_sprite;
};
