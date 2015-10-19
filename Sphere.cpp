//
//  Sphere.cpp
//  Monte-Carlo-Raytracer-Project
//

#include "Sphere.hpp"

// Constructor
Sphere::Sphere(glm::vec3 ce, float r, glm::vec3 co) {
    center = ce;
    radius = r;
    color = co;
};