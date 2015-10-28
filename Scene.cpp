//
//  Scene.cpp
//  Monte-Carlo-Raytracer-Project
//

#include "Scene.hpp"

#define M_PI 3.14159265358979323846

Scene::Scene(std::vector<Surface*>* o) {
    objects = o;
    
    maxBounces = 6;
    maxDepth = 9999.0;
    fov = 90 * M_PI / 180.0; // angle to radians
    
    cameraPos = glm::vec3(0.0, 0.0, 0.0);
    cameraDir = glm::vec3(0.0, 0.0, -1.0);
}