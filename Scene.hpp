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
    std::vector<Surface*>* objects;
    int maxBounces;
    float maxDepth;
    float fov;
    
    glm::vec3 cameraPos;
    glm::vec3 cameraDir;
    glm::vec3 cameraUp;
    
    Scene(std::vector<Surface*>* o);
};

#endif /* Scene_hpp */
