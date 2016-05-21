#ifndef PLANET_HH
#define PLANET_HH

#include <SolarSystem/object/object.hh>

class Planet : public Object {
public:
    Planet(const std::string &name, float radius, float orbitRadius, float translationPeriod, float rotationPeriod);

    // Virtual methods
    void iterate();
    void draw();

private:
    // Planet definition
    float _radius;
    float _orbitRadius;
    float _translationPeriod;
    float _rotationPeriod;
};

#endif // PLANET_HH
