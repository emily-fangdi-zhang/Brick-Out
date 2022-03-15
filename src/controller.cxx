// YOU DEFINITELY NEED TO MODIFY THIS FILE.

#include "controller.hxx"
#include "model.hxx"

// Data members that are references cannot be initialized by assignment
// in the constructor body and must be initialized in a member
// initializer list.
Controller::Controller(Model& model)
        : model(model),
          view(model)
{ }

///
/// CONTROLLER FUNCTIONS
///

// You can get a `Key` representing space with `ge211::Key::code(' ')`.
void
Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q')) {
        quit();
    }

    if (key == ge211::Key::code(' ')) {
        model.launch();
    }
}

// Makes the ball live via `Model::launch()`.
//
// NOTE: The solution is 1 line of code containing 15 non-whitespace
// characters.
void
Controller::on_mouse_up(ge211::Mouse_button, ge211::Posn<int>)
{
    model.launch();
}

// Informs the model of the mouse position (and thus the desired paddle
// position) via `Model::paddle_to(Position)`.
//
// NOTE: This can be done in 1 line as well.
void
Controller::on_mouse_move(ge211::Posn<int> position)
{
    model.paddle_to(position.x);
}


//
// Forwarding functions (done for you)
//

void
Controller::on_frame(double dt)
{
    model.on_frame(dt);
}

ge211::Dims<int>
Controller::initial_window_dimensions() const
{
    return view.initial_window_dimensions();
}

void
Controller::draw(ge211::Sprite_set& sprites)
{
    view.draw(sprites);
}
