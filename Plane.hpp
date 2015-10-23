//
//  Plane.hpp
//  Monte-Carlo-Raytracer-Project
//

#ifndef Plane_hpp
#define Plane_hpp

#include <stdio.h>
#include "Surface.hpp"

class Plane : public Surface {
private:
    glm::vec3 normal;
    glm::vec3 point;
    
public:
    Plane(glm::vec3 n, glm::vec3 c, glm::vec3 p);
    bool intersects(glm::vec3 rayOrig, glm::vec3 rayDir, float &t0, float &t1);
    glm::vec3 getNormal(glm::vec3 pos);
};

#endif /* Plane_hpp */
