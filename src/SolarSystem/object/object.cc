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
#include <GL/glut.h>

Object::Object(const std::string &name, const char* imgname) : _name(name) {
    _quad = gluNewQuadric();
    _img = loadBMP(imgname);

    int img_width = _img->width;
    int img_height = _img->height;
    char *img_data = _img->pixels;

    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    delete _img;

    _pos.set(0.0, 0.0, 0.0);
    _rotation = 0;
    _lastRotation = 0;
}

void Object::drawSphere(const Position &pos, float rotation, int radius) {
    glPushMatrix();

    // Translate to position
    glTranslatef(pos.x(), pos.y(), pos.z());

    // Rotation
    if(_name!="Space")
        glRotatef(rotation*180/3.14, 0.0f, 0.0f, 1.0f);

    // Texture sphere
    if(_name=="Sun")
        glEnable(GL_LIGHT1);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, _texture);
    gluQuadricNormals(_quad, GLU_SMOOTH);
    gluQuadricTexture(_quad, GL_TRUE);

    // Material
    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

    GLfloat mat_shininess = 30.0f;
    if(_name=="Sun")
        mat_shininess = 5.0f;
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

    GLfloat mat_emission[] = {0.05f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

    // Draw sphere
    gluSphere(_quad, radius, MESH_SIZE, MESH_SIZE);

    // Saturn rings
    if(_name=="Saturn") {
        glRotatef(-rotation*180/3.14, 0.0f, 0.0f, 1.0f);
        glRotatef(10, 0.0f, 1.0f, 0.0f);
        glutSolidTorus(0.05*radius, 1.45*radius, 2, MESH_SIZE);
        glutSolidTorus(0.15*radius, 1.75*radius, 2, MESH_SIZE);
    }

    glDisable(GL_TEXTURE_2D);
    if(_name=="Sun")
        glDisable(GL_LIGHT1);

    glPopMatrix();
}
