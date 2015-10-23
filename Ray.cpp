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
    
    // Ray termination
    if (depth > scene->maxDepth || bounces > scene->maxBounces) {
        std::cout << "EXTERMINATE\n";
        return glm::vec3(0.0, 0.0, 0.0);
    }
    
    
	// Compare ray with every object in scene
	// Find the smallest distance to an object
	float t0, t1, tNear = INF;
    Surface *s = nullptr; // Pointer to closest object
    
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
        
        // If the closes object is a light, return light color
        if (s->isLight())
            return s->color;
        
        glm::vec3 color(0.0, 0.0, 0.0);
        
        // If the object is reflective or refractive, calculate new ray(s)
        if (s->isReflective() || s->isRefractive()) {
            // If the object is refractive, create refractive ray
            if (s->isRefractive()) {
                // First check if the current point is inside the object
         
                // Calculate new refractive ray
                // Trace ray
            }
         
            // Calculate reflective ray for both refracive and reflective materials
            // Trace reflective ray
        }
        
        // Material is diffuse, do Monte Carlo stuff
        else {
            // russian roulette
            // random new ray over hemisphere of normal
            
            color = s->color;
        }
        
        // p is the point of intersection
        // pDir is a normalized vector from p towards light source
        glm::vec3 p = rayOrig + rayDir * tNear;
        glm::vec3 pDir = scene->lightPos1 - p;
        float dist = glm::length(pDir);
        pDir = glm::normalize(pDir);
        
        // Shoot shadow ray(s) to random position on light (not random not though)
        // Does not account for any sphere that is a light at the moment
        for (auto &o : *scene->objects)
            if (o->intersects(p, pDir, t0, t1))
                if (t0 < dist && !o->isLight()) return glm::vec3(0.0, 0.0, 0.0);
        
        return color;
    }

	return glm::vec3(0.0, 0.0, 0.0);
}