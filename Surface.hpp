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
    bool light = false;
    bool reflective = false;
    bool refractive = false;
public:
    glm::vec3 color;
    virtual bool intersects(glm::vec3 rayOrig, glm::vec3 rayDir, float &t0, float &t1) { return false; }
    
    void setLight() { light = true; };
    void setRefractive() { refractive = true; };
    void setReflective() { reflective = true; };
    
    bool isLight() { return light; }
    bool isRefractive() { return refractive; }
    bool isReflective() { return reflective; }
};

#endif /* Surface_hpp */
