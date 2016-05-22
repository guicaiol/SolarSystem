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

#include "planet.hh"
#include <math.h>

#define SCALE_RADIUS 1.0
#define SCALE_ORBITRADIUS 2
#define SCALE_TRANSLATION 500

#define TWOPI 6.14

Planet::Planet(const std::string &name, float radius, float orbitRadius, float translationPeriod, float rotationPeriod) : Object(name) {
    _radius = SCALE_RADIUS*radius;
    _orbitRadius = SCALE_ORBITRADIUS*orbitRadius;
    _translationPeriod = SCALE_TRANSLATION*translationPeriod;
    _rotationPeriod = rotationPeriod;
}

void Planet::iterate() {

    // Calculate iteration
    float currAng = atan2(_pos.y(), _pos.x());
    float angVel = (_translationPeriod==0? 0 : TWOPI/_translationPeriod);
    float newAng = currAng + angVel;

    // Orbit translation
    _pos.set(_orbitRadius*cos(newAng), _orbitRadius*sin(newAng), 0);
}

void Planet::draw() {
    // Draw planet
    Object::drawSphere(_pos, _radius, Colors::WHITE);

    // Draw orbit circle
    glBegin(GL_LINE_LOOP);
    glColor3f(0.8, 0.8, 0.8);
    for(float theta = 0; theta < TWOPI; theta+=0.15)   {
        float x = _orbitRadius * cos(theta);
        float y = _orbitRadius * sin(theta);
        glVertex3f(x, y, 0.0);
    }
    glEnd();

}
