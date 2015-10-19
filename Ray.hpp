//
//  Ray.hpp
//  Monte-Carlo-Raytracer-Project
//

#ifndef Ray_hpp
#define Ray_hpp

#include <stdio.h>
#include <vector>
#include "Surface.hpp"

class Ray
{
private:
    std::vector<Surface> *surfaces;
    
public:
    Ray(std::vector<Surface> *s);
    glm::vec3 trace(glm::vec3 rayOrig, glm::vec3 rayDir, float depth);
};

#endif /* Ray_hpp */
