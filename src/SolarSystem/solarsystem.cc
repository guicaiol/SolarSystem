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

#include "solarsystem.hh"
#include <iostream>
#include <math.h>

#define SENS_ROT	5.0
#define SENS_OBS	10.0
#define SENS_TRANSL	10.0

SolarSystem* SolarSystem::_instance = NULL;

SolarSystem::SolarSystem() {
    SolarSystem::_instance = this;
}

void SolarSystem::start(int argc, char *argv[]) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

    // Create window
    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
    int windowWidth = screenWidth/1.3;
    int windowHeight = screenHeight/1.3;
    int windowPosX = (screenWidth - windowWidth)/2;
    int windowPosY = (screenHeight - windowHeight)/2;

    glutInitWindowPosition(windowPosX, windowPosY);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Solar System");

    // Event functions
    _instance = this;
    glutDisplayFunc(SolarSystem::drawCallback);
    glutReshapeFunc(SolarSystem::reshapeCallback);
    glutMouseFunc(SolarSystem::mouseCallback);
    glutMotionFunc(SolarSystem::motionCallback);
//    glutKeyboardFunc(keyboardHandler);
//    glutSpecialFunc(specialKeysHandler);

    // Initialize
    initialize();

    // Start OpenGL main loop
    glutMainLoop();
}

void SolarSystem::initialize() {
    // Background color
    glClearColor(0.1, 0.1, 0.1, 0.0);

    // Models
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    // Lighting
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);

    GLfloat mat_shininess[] = {50.0};
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // Initialize observator rotation
    _obs_rotX = -40;
    _obs_rotY = 0;
    _obs_rotZ = 0;

    // Initialize observator position
    _obs_posX = 0;
    _obs_posY = 0;
    _obs_posZ = 10000;

    // Create planets
//    _planets.push_back(new Planet("Sun",     320, 0, 0,   0));
    _planets.push_back(new Planet("Mercury", 35.634, 250, 0.24,    0));
    _planets.push_back(new Planet("Venus",   46.000, 400,  0.62,   0));
    _planets.push_back(new Planet("Earth",   58.268, 650,  1.00,   0));
    _planets.push_back(new Planet("Mars",    30.361, 950,  1.68,   0));
    _planets.push_back(new Planet("Jupiter", 174.4,  1300,  9.86,  0));
    _planets.push_back(new Planet("Saturn",  131.8,  1727, 24.46,  0));
    _planets.push_back(new Planet("Uranus",  87.4,   2070, 74.01,  0));
    _planets.push_back(new Planet("Neptune", 83.3,   2697, 124.80, 0));
    _planets.push_back(new Planet("Pluto",   22.104, 3213, 228.53, 0));
}

void SolarSystem::drawEvent() {
    // Clear window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Planets
    for(unsigned i=0; i<_planets.size(); i++) {
        Planet *planet = _planets.at(i);
        planet->iterate();
        planet->draw();
    }

    // Sun (Light 0)
    GLfloat pos0[] = {0.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, pos0);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0002);
    glEnable(GL_LIGHT0);

    // Executa os comandos OpenGL
    glutSwapBuffers();
    glutPostRedisplay();
}

void SolarSystem::reshapeEvent(GLsizei width, GLsizei height) {
    // Set view port
    glViewport(0, 0, width, height);

    // Calc aspect correction
    _aspect = (GLfloat)width/(GLfloat)height;
    checkVisualizationParams();
}

void SolarSystem::mouseEvent(int button, int state, int x, int y) {
    if(state==GLUT_DOWN) {
        // Save current parameters
        _x_ini = x;
        _y_ini = y;
        _obsX_ini = _obs_posX;
        _obsY_ini = _obs_posY;
        _obsZ_ini = _obs_posZ;
        _rotX_ini = _obs_rotX;
        _rotY_ini = _obs_rotY;
        _rotZ_ini = _obs_rotZ;
        _button = button;

    } else {
        _button = -1;
    }
}

void SolarSystem::motionEvent(int x, int y) {
    // Calc deltas
    const int deltax = _x_ini - x;
    const int deltay = _y_ini - y;

    // Left button
    switch(_button) {
        case GLUT_LEFT_BUTTON: {
            _obs_rotZ = _rotZ_ini - deltax/SENS_ROT;
        } break;

        case GLUT_RIGHT_BUTTON: {
            _obs_posZ = _obsZ_ini + deltay/SENS_OBS;
        } break;

        case GLUT_MIDDLE_BUTTON: {
//            _obs_posX = _obsX_ini + deltax/SENS_TRANSL;
//            _obs_posY = _obsY_ini - deltay/SENS_TRANSL;
        } break;

    }

    // Repositionate observator
    positionateObservator();

    // Flush
    glutPostRedisplay();
}

void SolarSystem::positionateObservator() {
    // Coordinate system
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Positionate
    glTranslatef(-_obs_posX, -_obs_posY, -_obs_posZ);
    glRotatef(_obs_rotX, 1, 0, 0);
    glRotatef(_obs_rotY, 0, 1, 0);
    glRotatef(_obs_rotZ, 0, 0, 1);
}

void SolarSystem::checkVisualizationParams() {
    // Coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Projection
    gluPerspective(40, _aspect, 0.1, 100000);

    // Repositionate observator
    positionateObservator();
}
