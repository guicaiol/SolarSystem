
#include "position.hh"

Position::Position() {
    set(0, 0, 0);
}

Position::Position(float x, float y, float z) {
    set(x, y, z);
}

void Position::set(float x, float y, float z) {
    _x = x;
    _y = y;
    _z = z;
}
