//
//  Sphere.hpp
//  Monte-Carlo-Raytracer-Project
//  Derived class from Surface
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include <stdio.h>
#include "Surface.hpp"

class Sphere : public Surface
{
private:
    glm::vec3 center;
    float radius;
    glm::vec3 color;
    
public:
    Sphere(glm::vec3 ce, float r, glm::vec3 co);
};

#endif /* Sphere_hpp */
