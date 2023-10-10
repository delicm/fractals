#include "fractal.hpp"
#include "examples.hpp"

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
        fractal.process_img();
        refresh_image(fractal, texture, sprite);
        LOG("Color scheme changed");
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

    Fractal fractal (frac_example::basic, 250);
    fractal.set_radius();
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