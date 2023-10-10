#include <math.h>
#include "inner_fractal.hpp"

inline CPLX_TYPE norm(const complex number) {
    return sqrt(number.real*number.real + number.imag*number.imag);
}


template<int WIDTH, int HEIGHT>
void Fractal<WIDTH, HEIGHT>::set_c(const complex c) {
    m_julia = c;
}


template<int WIDTH, int HEIGHT>
void Fractal<WIDTH, HEIGHT>::set_res(const CPLX_TYPE res) {
    m_resolution = res;
    m_radius = res * std::max(HEIGHT, WIDTH) / 2;
}


template<int WIDTH, int HEIGHT>
void Fractal<WIDTH, HEIGHT>::set_iter(const int max_iter) {
    m_iterlim = max_iter;
}


template<int WIDTH, int HEIGHT>
inline complex Fractal<WIDTH, HEIGHT>::get_cplx_num(const int row, const int col) {
    return {
        .real = (col - WIDTH/2) * m_resolution,
        .imag = (HEIGHT/2 - row) * m_resolution
    };
}


template<int WIDTH, int HEIGHT>
void Fractal<WIDTH, HEIGHT>::set_radius(const CPLX_TYPE radius) {
    m_radius = radius;
    m_resolution = 2 * radius / std::min(WIDTH, HEIGHT);
}


template<int WIDTH, int HEIGHT>
void Fractal<WIDTH, HEIGHT>::set_radius() {
    double new_radius = (1 + sqrt(1+4*norm(m_julia))) / 2 + 0.01;
    set_radius((CPLX_TYPE) new_radius);
}


template<int WIDTH, int HEIGHT>
void Fractal<WIDTH, HEIGHT>::set_func(ApplyFunction f) {
    switch (f) {
        default:
        m_func = std::bind(&Fractal<WIDTH, HEIGHT>::f_std, this, std::placeholders::_1);
    }
}


template<int WIDTH, int HEIGHT>
void Fractal<WIDTH, HEIGHT>::set_colf(ColorFunction f) {
    switch (f) {
        case red_gradient:
        m_col = std::bind(&Fractal<WIDTH, HEIGHT>::cm_heatgrad, this, std::placeholders::_1);
        break;

        case multicolor:
        m_col = std::bind(&Fractal<WIDTH, HEIGHT>::cm_multicolor, this, std::placeholders::_1);
        break;

        default:
        m_col = std::bind(&Fractal<WIDTH, HEIGHT>::cm_blackwhite, this, std::placeholders::_1);
    }
}


/***************************************************************************************
* SFML COMMUNICATIONS
****************************************************************************************/

template<int WIDTH, int HEIGHT>
sf::Image Fractal<WIDTH, HEIGHT>::get_sfml_image() {
    sf::Image image;
    image.create(WIDTH, HEIGHT, m_img);
    return image;
}