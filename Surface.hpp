//
//  Surface.hpp
//  Monte-Carlo-Raytracer-Project
//  Base class for surfaces
//  Surfaces are for example spheres, walls and boxes
//

#ifndef Surface_hpp
#define Surface_hpp

#include <stdio.h>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/vec3.hpp"

class Surface
{
private:
    
public:
    glm::vec3 color;
    
    virtual bool intersects(glm::vec3 rayOrig, glm::vec3 rayDir, float &t0, float &t1) { return false; }
};

#endif /* Surface_hpp */
