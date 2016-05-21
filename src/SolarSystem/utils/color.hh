#ifndef COLOR_HH
#define COLOR_HH

class Color {
public:
    Color(float r, float g, float b, float a);

    // Getters
    float r() const { return _r; }
    float g() const { return _g; }
    float b() const { return _b; }
    float a() const { return _a; }

private:
    float _r;
    float _g;
    float _b;
    float _a;
};

namespace Colors {
    static const Color BLACK = Color(0, 0, 0, 1);
    static const Color WHITE = Color(1, 1, 1, 1);
    static const Color RED = Color(1, 0, 0, 1);
    static const Color GREEN = Color(0, 1, 0, 1);
    static const Color BLUE = Color(0, 0, 1, 1);
}

#endif // COLOR_HH
