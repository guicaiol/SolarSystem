
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

float rotate = 0;

void Object::drawSphere(const Position &pos, int radius, Color color) {

    glPushMatrix();

    // Translate to position
    glTranslated(pos.x(), pos.y(), pos.z());

    // Draw solid sphere
//    glColor4f(color.r(), color.g(), color.b(), color.a());
//    glutSolidSphere(radius, MESH_SIZE, MESH_SIZE);

    // Texture sphere
//    glBindTexture(GL_TEXTURE_2D, _texture);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    gluQuadricNormals(_quad, GLU_SMOOTH);
//    gluQuadricTexture(_quad, GL_TRUE);
    gluSphere(_quad, radius, MESH_SIZE, MESH_SIZE);

    glPopMatrix();
}
