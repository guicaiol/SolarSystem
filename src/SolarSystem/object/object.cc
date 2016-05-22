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

#include "object.hh"

Object::Object(const std::string &name) : _name(name) {
    _quad = gluNewQuadric();
    _img = loadBMP("../textures/earth.bmp");

    int img_width = _img->width;
    int img_height = _img->height;
    char *img_data = _img->pixels;

    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
}

void Object::drawSphere(const Position &pos, int radius, Color color) {

    glPushMatrix();

    // Translate to position
    glTranslated(pos.x(), pos.y(), pos.z());

    // Draw solid sphere
    glColor4f(color.r(), color.g(), color.b(), color.a());
    glutSolidSphere(radius, MESH_SIZE, MESH_SIZE);

    // Texture sphere
//    glBindTexture(GL_TEXTURE_2D, _texture);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    gluQuadricNormals(_quad, GLU_SMOOTH);
//    gluQuadricTexture(_quad, GL_TRUE);
//    gluSphere(_quad, radius, MESH_SIZE, MESH_SIZE);

    glPopMatrix();
}
