#ifndef CS40SPHERE_H
#define CS40SPHERE_H

#include "shape.h"
#include "common.h"

namespace cs40{

class Sphere : public Shape { 
protected:
    //TODO: add member variables
public:
    //TODO: add constructor

    ~Sphere() { /*do nothing*/ };

    //TODO: implement in sphere.cpp
    float hitTime(const cs40::Ray& r) const;
    vec3 normal(const vec3& p) const;
};

}

#endif
