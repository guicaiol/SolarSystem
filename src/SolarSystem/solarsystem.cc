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

#define SENS_ROT	10.0
#define ZOOM_PER_SCROLL 3

SolarSystem* SolarSystem::_instance = NULL;

SolarSystem::SolarSystem() {
    SolarSystem::_instance = this;
}

void SolarSystem::start(int argc, char *argv[]) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_ALPHA);

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
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

    // Initialize observator rotation
    _obs_rotX = -50;
    _obs_rotY = 0;
    _obs_rotZ = 0;

    // Initialize observator position
    _obs_posX = 0;
    _obs_posY = 0;
    _obs_posZ = SCALE_RADIUS*3400;

    // Create sun
    _objects.push_back(new Planet("Sun", 160, 0, 0, 24.47, "../textures/sun.bmp"));

    // Create planets

    _objects.push_back(new Planet("Mercury", 35.634, 250,     88,   58.6, "../textures/mercury.bmp"));
    _objects.push_back(new Planet("Venus",   46.000, 400,    224,    243, "../textures/venus.bmp"));

    Planet *earth = NULL;
    _objects.push_back(earth = new Planet("Earth",   56.268, 650,    365, 0.9958, "../textures/earth.bmp"));
    earth->setMoon(19.340, 70, 27.322, 3.232, "../textures/moon.bmp");

    _objects.push_back(new Planet("Mars",    30.361, 950,    687, 1.0208, "../textures/mars.bmp"));
    _objects.push_back(new Planet("Jupiter", 162.4,  1300,  4307,  0.396, "../textures/jupiter.bmp"));
    _objects.push_back(new Planet("Saturn",  131.8,  1727, 10731,  0.416, "../textures/saturn.bmp"));
    _objects.push_back(new Planet("Uranus",  87.4,   2070, 30660,   0.66, "../textures/uranus.bmp"));
    _objects.push_back(new Planet("Neptune", 82.3,   2697, 60152,   0.75, "../textures/neptune.bmp"));
    _objects.push_back(new Planet("Pluto",   22.104, 3213, 90491,  0.639, "../textures/pluto.bmp"));

    // Create space dome
    _objects.push_back(new Planet("Space", 5000, 0.0, 0.0, 0.0, "../textures/spacedome.bmp"));
}

void SolarSystem::drawEvent() {
    // Clear window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Planets
    for(unsigned i=0; i<_objects.size(); i++) {
        Planet *planet = _objects.at(i);
        planet->iterate(Position());
        planet->draw();
    }

    // Sun point light (Light 0)
    GLfloat pos0[] = {0.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, pos0);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0002);
    glEnable(GL_LIGHT0);

    // Sun sphere light (Light 1)
    GLfloat sun_ambient = 0.6f;
    GLfloat l1_ambient[] = {sun_ambient, sun_ambient, sun_ambient, 1.0f};
    glLightfv(GL_LIGHT1, GL_AMBIENT, l1_ambient);

    GLfloat sun_specular = 1.0f;
    GLfloat l1_specular[] = {sun_specular, sun_specular, sun_specular, 1.0f};
    glLightfv(GL_LIGHT1, GL_SPECULAR, l1_specular);

    GLfloat sun_diffuse = 0.0f;
    GLfloat l1_diffuse[] = {sun_diffuse, sun_diffuse, sun_diffuse, 1.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, l1_diffuse);

    // Light model properties
    GLfloat ambient = 0.175f;
    GLfloat model_ambient[] = {ambient, ambient, ambient, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

    // Fog
    GLfloat fogColor[4]= {0.4f, 0.4f, 0.4f, 1.0f};
    glFogi(GL_FOG_MODE, GL_EXP);
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogf(GL_FOG_DENSITY, 0.0005f);
    glEnable(GL_FOG);

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

    if(button==3) {
        _obs_posZ -= ZOOM_PER_SCROLL;
        if(_obs_posZ <= SCALE_RADIUS*1000)
            _obs_posZ = SCALE_RADIUS*1000;

        // Repositionate observator
        positionateObservator();

        // Flush
        glutPostRedisplay();

        return;
    } else if(button==4) {
        _obs_posZ += ZOOM_PER_SCROLL;
        if(_obs_posZ >= SCALE_RADIUS*4900)
            _obs_posZ = SCALE_RADIUS*4900;

        // Repositionate observator
        positionateObservator();

        // Flush
        glutPostRedisplay();

        return;
    }

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
            _obs_rotX = _rotX_ini + deltay/SENS_ROT;

            // Limit rotation
            if(_obs_rotX < -80)
                _obs_rotX = -80;
            if(_obs_rotX > 0)
                _obs_rotX = 0;

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
    gluPerspective(40, _aspect, 0.1, 20000);

    // Repositionate observator
    positionateObservator();
}
