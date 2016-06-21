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

#ifndef OBJECT_HH
#define OBJECT_HH

#include <string>
#include <GL/glut.h>
#include <SolarSystem/utils/color.hh>
#include <SolarSystem/utils/position.hh>

#include <3rdparty/imageloader.hh>

#define MESH_SIZE 100

class Object {
public:
    Object(const std::string &name, const char* imgname);

    // Getters
    std::string name() const { return _name; }
    Position pos() const { return _pos; }

    // Virtual pure methods
    virtual void iterate() = 0;
    virtual void draw() = 0;

protected:
    // Drawing functions
    void drawSphere(const Position &pos, int radius, Color color);

    // Object position
    Position _pos;
private:
    // Object name
    const std::string _name;

    Image *_img;
    GLuint _texture;
    GLUquadric* _quad;
};

#endif // OBJECT_HH
