//
//  Scene.cpp
//  Monte-Carlo-Raytracer-Project
//

#include "Scene.hpp"

Scene::Scene(std::vector<Surface>* o) {
    objects = o;
    
    maxBounces = 1;
    maxDepth = 10.0;
    fov = 90 * M_PI / 180.0; // angle to radians
    
    cameraPos = glm::vec3(0.0, 0.0, 0.0);
    cameraDir = glm::vec3(0.0, 0.0, -1.0);
    cameraUp = glm::vec3(0.0, 0.0, 0.0);
    
    lightPos1 = glm::vec3(0.0, 0.0, 0.0);
}