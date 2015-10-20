//
//  Scene.hpp
//  Monte-Carlo-Raytracer-Project
//  Wrapper for objects and constants
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include <vector>
#include "Surface.hpp"

class Scene
{
public:
    std::vector<Surface>* objects;
    int bounces = 1;
    float maxDepth = 10.0;
    
    glm::vec3 lightPos1;
    
    Scene(std::vector<Surface>* o) { objects = o; }
};

#endif /* Scene_hpp */
