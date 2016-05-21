
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
