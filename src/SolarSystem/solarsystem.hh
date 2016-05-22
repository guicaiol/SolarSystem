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

#ifndef SOLARSYSTEM_HH
#define SOLARSYSTEM_HH

#include <GL/glut.h>
#include <vector>
#include <SolarSystem/object/planet/planet.hh>

class SolarSystem {
public:
    SolarSystem();

    void start(int argc, char *argv[]);

private:

    // Internal
    void initialize();
    void positionateObservator();
    void checkVisualizationParams();

    // OpenGL callbacks
    static SolarSystem* _instance;
    static void drawCallback() { _instance->drawEvent(); }
    static void reshapeCallback(GLsizei width, GLsizei height) { _instance->reshapeEvent(width, height); }
    static void mouseCallback(int button, int state, int x, int y) { _instance->mouseEvent(button, state, x, y); }
    static void motionCallback(int x, int y) { _instance->motionEvent(x, y); }

    // OpenGL events
    void drawEvent();
    void reshapeEvent(GLsizei width, GLsizei height);
    void mouseEvent(int button, int state, int x, int y);
    void motionEvent(int x, int y);

    // Planets
    std::vector<Planet*> _planets;

    GLfloat _aspect;
    GLfloat _obs_rotX, _obs_rotY, _obs_rotZ, _rotX_ini, _rotY_ini, _rotZ_ini;
    GLfloat _obs_posX, _obs_posY, _obs_posZ, _obsX_ini, _obsY_ini, _obsZ_ini;
    int _x_ini, _y_ini, _button;
};

#endif // SOLARSYSTEM_HH
