#include "fractal.hpp"

#include <iostream>
#define LOG(x) std::cout << x << std::endl

const int WIDTH = 1920;
const int HEIGHT = 1080;

void refresh_image(Fractal<WIDTH, HEIGHT> &fractal, sf::Texture &texture, sf::Sprite &sprite) {
    texture.loadFromImage(fractal.get_sfml_image());
    sprite = sf::Sprite(texture);
    LOG("Image reloaded");
}


void handle_key_press(
    sf::RenderWindow &window,
    sf::Event &event,
    Fractal<WIDTH, HEIGHT> &fractal,
    sf::Texture &texture,
    sf::Sprite &sprite
)
{
    switch (event.key.code)
    {
    case sf::Keyboard::Add:
        fractal.set_radius(fractal.get_radius() * 0.9);
        fractal.process_img();
        refresh_image(fractal, texture, sprite);
        LOG("Zoom in executed");
        break;

    case sf::Keyboard::Subtract:
        fractal.set_radius(fractal.get_radius() / 0.9);
        fractal.process_img();
        refresh_image(fractal, texture, sprite);
        LOG("Zoom out executed");
        break;

    case sf::Keyboard::Multiply:
        fractal.set_colf(static_cast<ColorFunction>(
            (fractal.get_colorf() + 1) % COLORFCOUNT
        ));
        fractal.reprocess_colors();
        refresh_image(fractal, texture, sprite);
        LOG("Color scheme changed");
        break;

    case sf::Keyboard::Down:
        fractal.shift_down();
        refresh_image(fractal, texture, sprite);
        LOG("Shifted down");
        break;

    case sf::Keyboard::Up:
        fractal.shift_up();
        refresh_image(fractal, texture, sprite);
        LOG("Shifted up");
        break;

    case sf::Keyboard::Left:
        fractal.shift_left();
        refresh_image(fractal, texture, sprite);
        LOG("Shifted left");
        break;

    case sf::Keyboard::Right:
        fractal.shift_right();
        refresh_image(fractal, texture, sprite);
        LOG("Shifted right");
        break;

    case sf::Keyboard::Divide:
        fractal.load_example(static_cast<FractalExample>(
            (fractal.get_example() + 1) % EXCOUNT
        ));
        fractal.process_img();
        refresh_image(fractal, texture, sprite);
        LOG("Switched example");
        break;

    case sf::Keyboard::D:
        fractal.set_iter(
            50 + (fractal.get_iterlim() + 100) % 400
        );
        fractal.process_img();
        refresh_image(fractal, texture, sprite);
        LOG("Toggled iterlim (up)");
        break;

    case sf::Keyboard::A:
        fractal.set_iter(
            50 + (fractal.get_iterlim() + 300) % 400
        );
        fractal.process_img();
        refresh_image(fractal, texture, sprite);
        LOG("Toggled iterlim (down)");
        break;


    default:
        break;
    }
}


void handle_event(
    sf::RenderWindow &window,
    sf::Event &event,
    Fractal<WIDTH, HEIGHT> &fractal,
    sf::Texture &texture,
    sf::Sprite &sprite
)
{
    while (window.pollEvent(event)) {
    switch (event.type)
    {
        case sf::Event::Closed:
            window.close();
            LOG("Window closed");
            break;

        case sf::Event::KeyPressed:
            handle_key_press(window, event, fractal, texture, sprite);

        default:
            break;
    }
    }
}


void display_fractal() {

    Fractal fractal;
    fractal.load_example(basic);
    fractal.set_iter(250);
    fractal.set_radius();
    fractal.set_colf(heatgrad);
    LOG("Fractal loaded");

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Fractal", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    LOG("Window loaded");

    sf::Texture fractal_texture;
    sf::Sprite fractal_sprite;
    fractal.process_img();
    refresh_image(fractal, fractal_texture, fractal_sprite);
    LOG("Initial render complete");

    while (window.isOpen()){
        
        sf::Event event;
        handle_event(window, event, fractal, fractal_texture, fractal_sprite);

        window.clear();
        window.draw(fractal_sprite);
        window.display();
    }
    
}





int main() {

    display_fractal();

}