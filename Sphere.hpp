//
//  Sphere.hpp
//  Monte-Carlo-Raytracer-Project
//  Derived class from Surface
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include <stdio.h>
#include "Surface.hpp"
#include <cmath>
#include <math.h>

class Sphere : public Surface
{
private:
    glm::vec3 center;
    float radius;
	
    
public:
    Sphere(glm::vec3 ce, float r, glm::vec3 co);
	bool intersects(glm::vec3 rayOrig, glm::vec3 rayDir, float &t0, float &t1);
    glm::vec3 getNormal(glm::vec3 pos);
    glm::vec3 getCenter() { return center; };
    float getRadius() { return radius; };
};

#endif /* Sphere_hpp */
