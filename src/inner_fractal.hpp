#ifndef FRACTAL_H
#define FRACTAL_H

#include <SFML/Graphics.hpp>
#include <functional>

/************************************************************/

#define CPLX_TYPE float

typedef struct {
    CPLX_TYPE real;
    CPLX_TYPE imag;
} complex;

const int APPLYFCOUNT = 1;
enum ApplyFunction {
    standard
};

const int COLORFCOUNT = 3;
enum ColorFunction {
    black_white,
    heatgrad,
    multicolor
};


const int EXCOUNT = 5;
enum FractalExample {
    flower,
    spiralflower,
    thin,
    detailed,
    basic
};


/************************************************************/


inline CPLX_TYPE norm(const complex number);

template <int WIDTH = 1920, int HEIGHT = 1080>
class Fractal {
private:
    int m_iterlim;
    CPLX_TYPE m_resolution;
    CPLX_TYPE m_radius;
    complex m_julia;
    complex m_center = {0, 0};

    int* m_depth;
    sf::Uint8* m_img;

    ColorFunction m_current_colorf;
    FractalExample m_current_example;
    ApplyFunction m_current_func;

    std::function<complex(complex)> m_func;
    std::function<sf::Color(int)> m_col;

    inline complex f_std(const complex z);
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

    void set_c(const complex c);
    void set_res(const CPLX_TYPE res);
    void set_iter(const int max_iter);
    void set_radius(const CPLX_TYPE radius);
    void set_radius();
    void set_func(ApplyFunction f);
    void set_colf(ColorFunction f);
    void set_center(complex center);

    void load_example(FractalExample example);

    CPLX_TYPE get_radius();
    ColorFunction get_colorf();
    FractalExample get_example();
    ApplyFunction get_func();
    int get_iterlim();

    // Main Processing
    inline void set_pixel(const int row, const int col, const int val);
    int gauge_depth(const complex start);
    void processing_core(int rstart, int rend, int cstart, int cend);
    
    inline void process_img();

    inline complex get_cplx_num(const int row, const int col);

    // Interaction helpers
    void reprocess_colors();
    void shift_down();
    void shift_up();
    void shift_left();
    void shift_right();

    // SFML communications
    sf::Image get_sfml_image();
};

#endif