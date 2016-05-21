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
    Object(const std::string &name);

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
