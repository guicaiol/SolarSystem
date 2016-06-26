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
#include <iostream>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

#define SCALE_TRANSLATION 1
#define SCALE_ROTATION 55

#define TWOPI 6.28

Planet::Planet(const std::string &name, float radius, float orbitRadius, double translationPeriod, double rotationPeriod, const char* imgname) : Object(name, imgname) {
    _radius = SCALE_RADIUS*radius;
    _orbitRadius = SCALE_ORBITRADIUS*orbitRadius;
    _translationPeriod = SCALE_TRANSLATION*translationPeriod;
    _rotationPeriod = SCALE_ROTATION*rotationPeriod;

    srand(clock());
    _pos.set(rand()%100, rand()%100, 0.0);
}

void Planet::iterate() {
    // Translation
    double currAng = atan2(_pos.y(), _pos.x());
    double angVel = (_translationPeriod==0? 0 : TWOPI/_translationPeriod);
    double newAng = currAng + angVel;
    _pos.set(_orbitRadius*cos(newAng), _orbitRadius*sin(newAng), 0);

    // Rotation
    _rotation += (_rotationPeriod==0? 0 : TWOPI/_rotationPeriod);
}

void Planet::draw() {
    // Draw orbit circle
    glBegin(GL_LINE_LOOP);
    glColor4f(0.75, 0.75, 0.75, 1.0);
    for(float theta = 0; theta < TWOPI; theta+=0.10)   {
        float x = _orbitRadius * cos(theta);
        float y = _orbitRadius * sin(theta);
        glVertex3f(x, y, 0.0);
    }
    glEnd();

    // Draw planet
    Object::drawSphere(_pos, _rotation, _radius);
}
