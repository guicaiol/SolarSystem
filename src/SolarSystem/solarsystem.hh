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
