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
void Fractal<WIDTH, HEIGHT>::set_center(complex center) {
    m_center = center;
}





template<int WIDTH, int HEIGHT>
void Fractal<WIDTH, HEIGHT>::set_func(ApplyFunction f) {
    switch (f) {
        default:
        m_func = std::bind(&Fractal<WIDTH, HEIGHT>::f_std, this, std::placeholders::_1);
        m_current_func = standard;
        break;
    }
}


template<int WIDTH, int HEIGHT>
void Fractal<WIDTH, HEIGHT>::set_colf(ColorFunction f) {
    switch (f) {
        case heatgrad:
        m_col = std::bind(&Fractal<WIDTH, HEIGHT>::cm_heatgrad, this, std::placeholders::_1);
        m_current_colorf = heatgrad;
        break;

        case multicolor:
        m_col = std::bind(&Fractal<WIDTH, HEIGHT>::cm_multicolor, this, std::placeholders::_1);
        m_current_colorf = multicolor;
        break;

        default:
        m_col = std::bind(&Fractal<WIDTH, HEIGHT>::cm_blackwhite, this, std::placeholders::_1);
        m_current_colorf = black_white;
        break;
    }
}



template<int WIDTH, int HEIGHT>
inline complex Fractal<WIDTH, HEIGHT>::get_cplx_num(const int row, const int col) {
    return {
        .real = (col - WIDTH/2) * m_resolution + m_center.real,
        .imag = (HEIGHT/2 - row) * m_resolution + m_center.imag
    };
}


template<int WIDTH, int HEIGHT>
int Fractal<WIDTH, HEIGHT>::get_iterlim() {
    return m_iterlim;
}


template<int WIDTH, int HEIGHT>
CPLX_TYPE Fractal<WIDTH, HEIGHT>::get_radius() {
    return m_radius;
}


template<int WIDTH, int HEIGHT>
ColorFunction Fractal<WIDTH, HEIGHT>::get_colorf() {
    return m_current_colorf;
}


template<int WIDTH, int HEIGHT>
FractalExample Fractal<WIDTH, HEIGHT>::get_example() {
    return m_current_example;
}


template<int WIDTH, int HEIGHT>
ApplyFunction Fractal<WIDTH, HEIGHT>::get_func() {
    return m_current_func;
} 




template<int WIDTH, int HEIGHT>
void Fractal<WIDTH, HEIGHT>::load_example(FractalExample example) {
    switch (example)
    {
    case flower:
        set_c({-0.4, 0.6});
        m_current_example = flower;
        break;

    case spiralflower:
        set_c({0.285, 0.01});
        m_current_example = spiralflower;
        break;

    case thin:
        set_c({-0.835, -0.2321});
        m_current_example = thin;
        break;

    case detailed:
        set_c({-0.8, 0.156});
        m_current_example = detailed;
        break;

    case basic:
        set_c({-0.5251993, -0.5251993});
        m_current_example = basic;
        break;

    default:
        break;
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