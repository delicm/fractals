#include <string>

#include "fractal.hpp"

void test_display_fractal(
    const int iter = 100,
    complex c = {-0.5251993, -0.5251993}
)
{

    printf("Load fractal\n");
    const int width = 1920;
    const int height = 1080;

    Fractal<width, height> fractal(c);

    fractal.set_iter(iter);
    fractal.set_radius(1);
    fractal.set_colf(multicolor);

    /**********************************************/

    printf("Processing image\n");
    fractal.process_img();

    printf("Load image into SFML\n");
    sf::Image image = fractal.get_sfml_image();

    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Sprite sprite(texture);

    printf("Open window\n");
    sf::RenderWindow window(sf::VideoMode(width, height), "Fractal");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();

        window.draw(sprite);

        window.display();
    }

    printf("Window closed\n");

}


void generate_img(
    std::string name,
    const int iter = 100,
    complex c = {-0.5251993, -0.5251993}
)
{
    const int width = 1920;
    const int height = 1080;

    Fractal<width, height> fractal(c);

    fractal.set_iter(iter);
    fractal.set_radius(1);
    fractal.set_colf(multicolor);

    fractal.process_img();

    sf::Image image = fractal.get_sfml_image();

    image.saveToFile("../images/" + name + ".png");

}


int main() {

    int iters = 300;

    complex c1 = {
        .real = -0.8,
        .imag = 0.156
    };

    complex c2 = {
        .real = -0.835,
        .imag = -0.2321
    };

    complex c3 = {
        .real = -0.7269,
        .imag = 0.1889
    };

    test_display_fractal(iters, c1);
    // generate_img("logtrick", iters, c3);

}