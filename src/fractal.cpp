#include <math.h>
#include <thread>
#include <vector>

#include "inner_fractal.hpp"



/*** CONSTRUCTOR & DESTRUCTOR ***/

template<int WIDTH, int HEIGHT>
Fractal<WIDTH, HEIGHT>::Fractal(
    const complex c,
    const int iterlim,
    const CPLX_TYPE res
) : m_julia(c), m_iterlim(iterlim), m_resolution(res)
{
    m_img = (sf::Uint8*) malloc(sizeof(sf::Uint8) * WIDTH * HEIGHT * 4);
    m_depth = (int*) malloc(sizeof(int) * HEIGHT * WIDTH);

    m_func = std::bind(&Fractal<WIDTH, HEIGHT>::f_std, this, std::placeholders::_1);
    m_col = std::bind(&Fractal<WIDTH, HEIGHT>::cm_blackwhite, this, std::placeholders::_1);
    m_radius = m_resolution * std::max(HEIGHT, WIDTH) / 2;

    m_current_colorf = black_white;
}


template<int WIDTH, int HEIGHT>
Fractal<WIDTH, HEIGHT>::~Fractal() {
    free(m_img);
    free(m_depth);
}





/*** PROCESSING CORE ***/


template<int WIDTH, int HEIGHT>
inline void Fractal<WIDTH, HEIGHT>::set_pixel(const int row, const int col, const int val) {
    m_depth[row * WIDTH + col] = val;
    sf::Color color = m_col(val);
    int pix_num = 4 * (row * WIDTH + col);
    m_img[pix_num] = color.r;
    m_img[pix_num+1] = color.g;
    m_img[pix_num+2] = color.b;
    m_img[pix_num+3] = color.a;
}


template<int WIDTH, int HEIGHT>
int Fractal<WIDTH, HEIGHT>::gauge_depth(const complex start) {
    int counter = 0;
    complex current = {
        .real = start.real,
        .imag = start.imag
    };

    CPLX_TYPE escape_radius = (CPLX_TYPE) (1 + sqrt(1+4*norm(m_julia))) / 2 + 0.01;
    if (escape_radius < m_radius) escape_radius = m_radius;

    while (norm(current) < escape_radius && counter < m_iterlim) {
        counter++;
        current = m_func(current);
    }

    return counter;
}


template<int WIDTH, int HEIGHT>
void Fractal<WIDTH, HEIGHT>::processing_core(int rstart, int rend, int cstart, int cend) {

    const int num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    threads.reserve(num_threads);

    int total_rows = rend - rstart;
    int chunksize = total_rows / num_threads;

    for (int thnum = 0; thnum < num_threads; thnum++) {

        int h_start = rstart + chunksize * thnum;
        int h_end = (thnum == num_threads - 1) ? rend : rstart + chunksize * (thnum + 1);

        threads.emplace_back([this, h_start, h_end, cstart, cend]() {
            for (int row = h_start; row < h_end; row++) {
            for (int col = cstart; col < cend; col++) {
                set_pixel(
                    row, col,
                    gauge_depth(get_cplx_num(row, col))
                );
            }
            }
        });

    }

    for (std::thread& thread : threads) {
        thread.join();
    }

}



/*** IMAGE PROCESSING ***/


template<int WIDTH, int HEIGHT>
inline void Fractal<WIDTH, HEIGHT>::process_img() {
    processing_core(0, HEIGHT, 0, WIDTH);
}





