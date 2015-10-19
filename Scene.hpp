//
//  Scene.hpp
//  Monte-Carlo-Raytracer-Project
//  Acts as a wrapper for all the objects in the scene
//

#ifndef Scene_hpp
#define Scene_hpp

#include <stdio.h>
#include <vector>
#include "Surface.hpp"

class Scene
{
private:
    std::vector<Surface> surfaces;
    
public:
    void addSurface(Surface s);
    
};

#endif /* Scene_hpp */
