#ifndef POSITION_HH
#define POSITION_HH

class Position {
public:
    Position();
    Position(float x, float y, float z);

    // Getters
    float x() const { return _x; }
    float y() const { return _y; }
    float z() const { return _z; }

    // Setters
    void set(float x, float y, float z);

private:
    float _x;
    float _y;
    float _z;
};

#endif // POSITION_HH
