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
#include "Sphere.hpp"

class Scene
{
public:
    std::vector<Surface*>* objects;
    std::vector<Sphere*>* lights;
    int maxBounces;
    float maxDepth;
    float fov;
    
    glm::vec3 cameraPos;
    glm::vec3 cameraDir;
    glm::vec3 cameraUp;
    
    Scene(std::vector<Surface*>* o, std::vector<Sphere*>* l);
};

#endif /* Scene_hpp */
