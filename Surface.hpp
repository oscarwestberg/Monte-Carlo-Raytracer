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
    bool oren = false;
    bool refractive = false;
public:
    glm::vec3 color;
    
    // Pure virtual methods
    virtual bool intersects(glm::vec3 rayOrig, glm::vec3 rayDir, float &t0, float &t1) = 0;
    virtual glm::vec3 getNormal(glm::vec3 pos) = 0;
    
    void setLight() { light = true; };
    void setRefractive() { refractive = true; };
    void setOren() { oren = true; };
    
    bool isLight() { return light; }
    bool isRefractive() { return refractive; }
    bool isOren() { return oren; };
};

#endif /* Surface_hpp */
