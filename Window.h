#ifndef     WINDOW_H
#define     WINDOW_H

template <typename T>
class Window
{
private:
    T x_min, x_max, y_min, y_max;

public:
    Window(T _x_min, T _x_max, T _y_min, T _y_max)
        : x_min(_x_min), x_max(_x_max), y_min(_y_min), y_max(_y_max)
    {}

// Utility function for getting the size, width, and height of the window.
    T size() {
        return (width() * height());
    }

    T width() {
        return (x_max - x_min);
    }

    T height() {
        return (y_max - y_min);
    }

// Getters and setters for the window elements
    void xMin(T _x_min) { x_min = _x_min; }
    T xMin() { return x_min; }

    void xMax(T _x_max) { x_max = _x_max; }
    T xMax() { return x_max; }

    void yMin(T _y_min) { y_min = _y_min; }
    T yMin() { return y_min; }

    void yMax(T _y_max) { y_max = _y_max; }
    T yMax() { return y_max; }

// Reset all values
    void Reset(T _x_min, T _x_max, T _y_min, T _y_max) {
        x_min = _x_min;
        x_max = _x_max;
        y_min = _y_min;
        y_max = _y_max;
    }
};

#endif
