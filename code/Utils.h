#ifndef     UTILS_H
#define     UTILS_H

#include <complex>
#include <tuple>

#include "Window.h"

std::complex<double> Scale(Window<int> &scr, Window<double> &fract, std::complex<double> c);

std::tuple<int, int, int> RGB_Piecewise_Linear(int n, int iter_max);
std::tuple<int, int, int> RGB_Smooth(int n, int iter_max);

#endif
