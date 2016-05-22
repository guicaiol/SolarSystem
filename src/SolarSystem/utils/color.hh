/*
 * SCC0650 - Computação Gráfica
 * Universidade de São Paulo (USP) - São Carlos
 * Instituto de Ciências Matemáticas e de Computação (ICMC)
 * Autores: Guilherme Caixeta de Oliveira - nUSP 8504368
 *          Andressa Baptistine Andrião   - nUSP 7547020
 *          Lucas dos Santos Luchiari     - nUSP 8084260
 *
 * This file is part of SolarSystem project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
