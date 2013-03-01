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

void Mandelbrot()
{
    // Define the size of the image
    Window<int> scr(0, 1200, 0, 1200);
    // Define the domain in which we test for points
    Window<double> fract(-2.2, 1.2, -1.7, 1.7);

    // Lamba function used to calculate the factal
    auto func = [] (std::complex<double> z, std::complex<double> c) -> std::complex<double> { return z * z + c; };

    int iter_max = 500;
    const char *filename = "fractal.png";
    bool smooth_color = false;
    std::vector<int> colors(scr.size());
    
    Fractal(scr, fract, iter_max, colors, func, filename, smooth_color);
}
