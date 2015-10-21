//
//  Ray.cpp
//  Monte-Carlo-Raytracer-Project
//

#include "Ray.hpp"

#define INF 9999

Ray::Ray(Scene *s) {
    scene = s;
}

glm::vec3 Ray::trace(glm::vec3 rayOrig, glm::vec3 rayDir, float depth, int bounces) {
	// Compare ray with every object in scene
	// Find the smallest distance to an object
	float t0, t1, tNear = INF;
    Surface *s = nullptr;
    
	for (auto &o : *scene->objects) {
		if (o->intersects(rayOrig, rayDir, t0, t1)) {
            if (t0 < tNear) {
                tNear = t0;
                s = o;
            }
		}
	}
    
    // We have found an object
    if (s != nullptr) {
        // p is the point of intersection
        // pDir is a normalized vector from p towards light source
        glm::vec3 p = rayOrig + rayDir * tNear;
        glm::vec3 pDir = scene->lightPos1 - p;
        float dist = glm::length(pDir);
        pDir = glm::normalize(pDir);
        
        // Look through all objects, if we find an object closer than the light source, shaded = true;
        for (auto &o : *scene->objects)
            if (o->intersects(p, pDir, t0, t1))
                if (t0 < dist) return glm::vec3(0.0, 0.0, 0.0);
        
        // Not shaded => return object's color
        return s->color;
    }
    
	return glm::vec3(0.0, 0.0, 0.0);
}