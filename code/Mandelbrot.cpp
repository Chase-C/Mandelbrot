#include <stdio.h>
#include <allegro5/allegro.h>
#include <complex>
#include <vector>
#include <functional>

#include "Window.h"
#include "Utils.h"

int Escape(std::complex<double> c, int iter_max,
            const std::function<std::complex<double>(std::complex<double>, std::complex<double>)> &func)
{
    std::complex<double> z(0);
    int iter = 0;

    while(abs(z) < 2.0 && iter < iter_max) {
        z = func(z, c);
        iter++;
    }

    return iter;
}

// Loop over each pixel and check if the point associated with it escapes to infinity
void get_number_iterations(Window<int> &scr, Window<double> &fract, int iter_max, std::vector<int> &colors,
            const std::function<std::complex<double>(std::complex<double>, std::complex<double>)> &func)
{
    int k = 0;
    for(int i = scr.yMin(); i < scr.yMax(); i++) {
        for(int j = scr.xMin(); j < scr.xMax(); j++) {
            std::complex<double> c((double) j, (double) i);
            c = Scale(scr, fract, c);
            colors[k] = Escape(c, iter_max, func);
            //std::tuple<int, int, int> rgb = RGB_Piecewise_Linear(colors[k], iter_max);
            std::tuple<int, int, int> rgb = RGB_Smooth(colors[k], iter_max);
            //printf("%i, %i\n", j, i);
            al_put_pixel(j, i, al_map_rgb(std::get<0>(rgb), std::get<1>(rgb), std::get<2>(rgb)));
            al_flip_display();
            k++;
        }
    }
}

void Fractal(Window<int> &scr, Window<double> &fract, int iter_max, std::vector<int> &colors,
            const std::function<std::complex<double>(std::complex<double>, std::complex<double>)> &func,
            const char *fname, bool smooth_color)
{
    get_number_iterations(scr, fract, iter_max, colors, func);
}

void Mandelbrot(Window<int> scr, Window<double> fract)
{
    // Lamba function used to calculate the factal
    auto func = [] (std::complex<double> z, std::complex<double> c) -> std::complex<double> { return z * z + c; };

    int iter_max = 500;
    const char *filename = "fractal.png";
    bool smooth_color = false;
    std::vector<int> colors(scr.size());
    
    Fractal(scr, fract, iter_max, colors, func, filename, smooth_color);
}
