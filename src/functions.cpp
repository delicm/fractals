#include "inner_fractal.hpp"

/*************************/
// FUNCTIONS
/*************************/


template<int WIDTH, int HEIGHT>
inline complex Fractal<WIDTH, HEIGHT>::f_std(const complex z) {
    return (complex) {
        .real = z.real*z.real - z.imag*z.imag + m_julia.real,
        .imag = 2*z.real*z.imag + m_julia.imag
    };
}

/*************************/
// COLORS
/*************************/


template<int WIDTH, int HEIGHT>
sf::Color Fractal<WIDTH, HEIGHT>::cm_blackwhite(const int depth) {
    return depth == m_iterlim ? 
           sf::Color(255, 255, 255):
           sf::Color(0, 0, 0);
}


template<int WIDTH, int HEIGHT>
sf::Color Fractal<WIDTH, HEIGHT>::cm_heatgrad(const int depth) {
    float pct = (float) depth / m_iterlim;
    sf::Uint8 intensity = (sf::Uint8) 255 * pct;
    return sf::Color(intensity, intensity, intensity);
}


template<int WIDTH, int HEIGHT>
sf::Color Fractal<WIDTH, HEIGHT>::cm_multicolor(const int depth) {
    static sf::Color colors[5] = {
        sf::Color(0,0,128),
        sf::Color(0,0,255),
        sf::Color(255,255,255),
        sf::Color(255,200,0),
        sf::Color(0,0,0)
    };

    int chunksize = (m_iterlim / 5);
    int chunk = depth / chunksize;
    float pct = (float) (depth % chunksize) / chunksize;

    return sf::Color(
        (sf::Uint8) colors[chunk].r * pct + colors[chunk+1].r * (1-pct),
        (sf::Uint8) colors[chunk].g * pct + colors[chunk+1].g * (1-pct),
        (sf::Uint8) colors[chunk].b * pct + colors[chunk+1].b * (1-pct)
    );
}