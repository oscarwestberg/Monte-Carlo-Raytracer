//
//  Plane.cpp
//  Monte-Carlo-Raytracer-Project
//

#include "Plane.hpp"

Plane::Plane(glm::vec3 n, glm::vec3 c, glm::vec3 p) {
    normal = n;
    color = c;
    point = p;
}


// Does ray intersect with this plane?
// Find a point p on the surface with rayOrig + rayDir * t = p
// If dot((p - point), normal) = 0 then the vector (p - point) is on the surface and thus,
// there exists a t that produces the point p so we solve t.
bool Plane::intersects(glm::vec3 rayOrig, glm::vec3 rayDir, float &t0, float &t1) {
    
    if (glm::dot(rayDir, normal) >= 0.0001) {
        t0 = glm::dot((point - rayOrig), normal) / glm::dot(rayDir, normal);
        return (t0 >= 0.0);
    }
    
    return false;
}