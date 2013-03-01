#include <complex>

#include "Window.h"
#include "Utils.h"

std::complex<double> Scale(Window<int> &scr, Window<double> &fract, std::complex<double> c)
{
    std::complex aux(c.real() / (double)scr.width() * fract.width() + fract.xMin(),
                     c.imag() / (double)scr.height() * fract.height() + fract.yMin());
    return aux;
}

std::tuple<int, int, int> RGB_Piecewise_Linear(int n, int iter_max)
{
    int N = 256;
    int N3 = N * N * N;

    // Map n on the 0-1 interval (real numbers)
    double t = (double)n / (double)iter_max;

    // Expand n on the 0-256^3 interval (integers)
    n = (int)(t * (double)N3);

    int b = n / (N * N);
    int nn = n - b * n * n;
    int r = nn / N;
    int g = nn - r * N;

    return std::tuple<int, int, int>(r, g, b);
}

std::tuple<int, int, int> RGB_Smooth(int n, int iter_max)
{
    // Map n on the 0-1 interval (real numbers)
    double t = (double)n / (double)iter_max;

    // Use smooth polynomials for r, g, and b
    int r = (int)(9 * (1 - t) * t * t * t * 255);
    int g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
    int b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);

    return std::tuple<int, int, int>(r, g, b);
}
