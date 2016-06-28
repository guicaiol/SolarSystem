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

#ifndef PLANET_HH
#define PLANET_HH

#define SCALE_RADIUS 0.1
#define SCALE_ORBITRADIUS 0.125

#include <SolarSystem/object/object.hh>

class Planet : public Object {
public:
    Planet(const std::string &name, float radius, float orbitRadius, double translationPeriod, double rotationPeriod, const char* imgname);

    // Virtual methods
    void iterate(const Position &center);
    void draw();

    // Moon config
    void setMoon(float radius, float orbitRadius, double translationPeriod, double rotationPeriod, const char* imgname);
private:
    // Planet definition
    float _radius;
    float _orbitRadius;
    double _translationPeriod;
    double _rotationPeriod;

    Position _lastCenter;

    // Moon
    bool _hasMoon;
    Planet *_moon;
};

#endif // PLANET_HH
