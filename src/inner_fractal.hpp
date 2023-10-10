#ifndef FRACTAL_H
#define FRACTAL_H

#include <SFML/Graphics.hpp>
#include <functional>

#define CPLX_TYPE float

typedef struct {
    CPLX_TYPE real;
    CPLX_TYPE imag;
} complex;

enum ApplyFunction {
    standard
};

enum ColorFunction {
    black_white,
    red_gradient,
    multicolor
};


inline CPLX_TYPE norm(const complex number);

template <int WIDTH = 1920, int HEIGHT = 1080>
class Fractal {
private:
    int m_iterlim;
    sf::Uint8* m_img;
    complex m_julia;
    CPLX_TYPE m_resolution;
    CPLX_TYPE m_radius;

    std::function<complex(complex)> m_func;
    std::function<sf::Color(int)> m_col;

    complex f_std(const complex z);
    sf::Color cm_blackwhite(int depth);
    sf::Color cm_heatgrad(int depth);
    sf::Color cm_multicolor(int depth);

public:
    // Boilerplate
    Fractal(
        const complex c = {-0.5251993, -0.5251993},
        const int iterlim = 50,
        const CPLX_TYPE res = 0.001
    );

    ~Fractal();

    inline void set_pixel(const int row, const int col, const int val);
    void set_c(const complex c);
    void set_res(const CPLX_TYPE res);
    void set_iter(const int max_iter);
    void set_radius(const CPLX_TYPE radius);
    void set_radius();
    void set_func(ApplyFunction f);
    void set_colf(ColorFunction f);

    // Processing
    int gauge_depth(const complex start);
    inline complex get_cplx_num(const int row, const int col);
    void process_img();

    // SFML communications
    sf::Image get_sfml_image();
};

#endif