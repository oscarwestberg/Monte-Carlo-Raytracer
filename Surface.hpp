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
	bool transparent = false;
public:
    glm::vec3 color;
    
    // Pure virtual methods
    virtual bool intersects(glm::vec3 rayOrig, glm::vec3 rayDir, float &t0, float &t1) = 0;
    virtual glm::vec3 getNormal(glm::vec3 pos) = 0;
    
    void setLight() { light = true; };
    void setRefractive() { refractive = true; };
    void setReflective() { reflective = true; };
	void setTransparent() { transparent = true; };

    bool isLight() { return light; }
    bool isRefractive() { return refractive; }
    bool isReflective() { return reflective; }
	bool isTransparent() { return transparent; }
};

#endif /* Surface_hpp */
