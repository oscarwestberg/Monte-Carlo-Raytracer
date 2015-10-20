//
//  Ray.hpp
//  Monte-Carlo-Raytracer-Project
//

#ifndef Ray_hpp
#define Ray_hpp

#include <stdio.h>
#include <vector>
#include "Surface.hpp"
#include "Scene.hpp"

class Ray
{
private:
    Scene* scene;
    
public:
    Ray(Scene *s);
    glm::vec3 trace(glm::vec3 rayOrig, glm::vec3 rayDir, float depth, int bounces);
};

#endif /* Ray_hpp */
