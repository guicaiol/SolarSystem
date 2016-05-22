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

#ifndef POSITION_HH
#define POSITION_HH

class Position {
public:
    Position();
    Position(float x, float y, float z);

    // Getters
    float x() const { return _x; }
    float y() const { return _y; }
    float z() const { return _z; }

    // Setters
    void set(float x, float y, float z);

private:
    float _x;
    float _y;
    float _z;
};

#endif // POSITION_HH
