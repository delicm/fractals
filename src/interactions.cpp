#include "inner_fractal.hpp"

#include <thread>
#include <vector>

const float SHIFT_PCT = 0.05;


template<int WIDTH, int HEIGHT>
void Fractal<WIDTH, HEIGHT>::reprocess_colors() {

    const int num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    threads.reserve(num_threads);

    const int CHUNK = HEIGHT / num_threads;

    for (int thnum = 0; thnum < num_threads; thnum++) {

        int h_start = CHUNK * thnum;
        int h_end = (thnum == num_threads - 1) ? HEIGHT : CHUNK * (thnum + 1);

        threads.emplace_back([this, h_start, h_end]() {
            for (int row = h_start; row < h_end; row++) {
            for (int col = 0; col < WIDTH; col++) {
                set_pixel(
                    row, col, m_depth[row * WIDTH + col]
                );
            }
            }
        });

    }

    for (std::thread& thread : threads) {
        thread.join();
    }
}




template<int WIDTH, int HEIGHT>
void Fractal<WIDTH, HEIGHT>::shift_down() {

    static int SHIFT_PIX = (int) ((float) SHIFT_PCT * HEIGHT);

    m_center = {
        .real = m_center.real,
        .imag = m_center.imag - SHIFT_PIX * m_resolution
    };
    
    for (int row = 0; row < HEIGHT - SHIFT_PIX; row++) {
        for (int col = 0; col < WIDTH; col++) {
            m_depth[row * WIDTH + col] = m_depth[(row + SHIFT_PIX) * WIDTH + col];
        }
    }

    processing_core(HEIGHT - SHIFT_PIX, HEIGHT, 0, WIDTH);

    reprocess_colors();

}


template<int WIDTH, int HEIGHT>
void Fractal<WIDTH, HEIGHT>::shift_up() {

    static int SHIFT_PIX = (int) ((float) SHIFT_PCT * HEIGHT);

    m_center = {
        .real = m_center.real,
        .imag = m_center.imag + SHIFT_PIX * m_resolution
    };
    
    for (int row = HEIGHT - 1; row >= SHIFT_PIX; row--) {
        for (int col = 0; col < WIDTH; col++) {
            m_depth[row * WIDTH + col] = m_depth[(row - SHIFT_PIX) * WIDTH + col];
        }
    }

    processing_core(0, SHIFT_PIX, 0, WIDTH);

    reprocess_colors();

}


template<int WIDTH, int HEIGHT>
void Fractal<WIDTH, HEIGHT>::shift_right() {

    static int SHIFT_PIX = (int) ((float) SHIFT_PCT * HEIGHT);

    m_center = {
        .real = m_center.real + SHIFT_PIX * m_resolution,
        .imag = m_center.imag
    };
    
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH - SHIFT_PIX; col++) {
            m_depth[row * WIDTH + col] = m_depth[row * WIDTH + col + SHIFT_PIX];
        }
    }

    processing_core(0, HEIGHT, WIDTH-SHIFT_PIX, WIDTH);

    reprocess_colors();

}



template<int WIDTH, int HEIGHT>
void Fractal<WIDTH, HEIGHT>::shift_left() {

    static int SHIFT_PIX = (int) ((float) SHIFT_PCT * HEIGHT);

    m_center = {
        .real = m_center.real - SHIFT_PIX * m_resolution,
        .imag = m_center.imag
    };
    
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = WIDTH - 1; col >= SHIFT_PIX; col--) {
            m_depth[row * WIDTH + col] = m_depth[row * WIDTH + col - SHIFT_PIX];
        }
    }

    processing_core(0, HEIGHT, 0, SHIFT_PIX);

    reprocess_colors();

}

