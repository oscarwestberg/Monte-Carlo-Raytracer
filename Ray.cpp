//
//  Ray.cpp
//  Monte-Carlo-Raytracer-Project
//

#include "Ray.hpp"

Ray::Ray(std::vector<Surface> *s) {
    surfaces = s;
}

glm::vec3 Ray::trace(glm::vec3 rayOrig, glm::vec3 rayDir, float depth) {
    glm::vec3 c(0.0, 255, 0.0);
    
    // Compare ray with every object in scene
    // Find the smallest distance to an object
    for (int i = 0; i < surfaces->size(); i++) {
        
    }
    
    // If we found an intersection, cast shadow ray
    // Compare shadow ray with every object
    
    
    // If point isn't in shadow, update with object's color and light's brightness
    
    
    
    return c;
}