//
//  Ray.cpp
//  Monte-Carlo-Raytracer-Project
//

#include "Ray.hpp"

#define INF 9999

Ray::Ray(Scene *s) {
    scene = s;
}

glm::vec3 refract(const glm::vec3 I, const glm::vec3 N, const float n) {
    return I;
}

glm::vec3 Ray::trace(glm::vec3 rayOrig, glm::vec3 rayDir, float depth, int bounces) {
    
    // Ray termination
    if (depth > scene->maxDepth || bounces > scene->maxBounces) {
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
    
        // p is the point of intersection
        // pDir is a normalized vector from p towards light source
        glm::vec3 color(0.0);
        glm::vec3 localColor(0.0);
        glm::vec3 p = rayOrig + rayDir * tNear;
        glm::vec3 pDir = scene->lightPos1 - p;
        glm::vec3 normal = s->getNormal(p);
        // r is the reflected direction
        glm::vec3 r = rayDir - 2 * glm::dot(rayDir, normal) * normal;
        
        float dist = glm::length(pDir);
        pDir = glm::normalize(pDir);
        
        bounces++;
        depth += dist;
        
        // If the object is reflective or refractive, calculate new ray(s)
        if (s->isReflective() || s->isRefractive()) {
            
            // If the object is refractive, create refractive ray
            if (s->isRefractive()) {
                // First check if the current point is inside the object
         
                // Calculate new refractive ray
                // Trace ray
                glm::vec3 t = refract(rayDir, normal, 1.2);
                Ray ray(scene);
                color += ray.trace(p, t, depth, bounces);
            }
         
            // Calculate reflective ray for both refracive and reflective materials
            // Trace reflective ray
            Ray ray(scene);
            color += ray.trace(p, r, depth, bounces);
        }
        
        // Material is diffuse, do Monte Carlo stuff
        else {
            // russian roulette
            // random new ray over hemisphere of normal
            Ray ray(scene);
            //color += ray.trace(p, normal, depth, bounces);
            
            // Material is diffuse - lambertian reflectance
            // We only have one light source
            float lambert = glm::dot(normal, pDir);
            localColor = s->color * lambert;
        }
        
        bool shaded = false;
        
        // Shoot shadow ray(s) to random position on light (not random not though)
        // Does not account for any sphere that is a light at the moment
        for (auto &o : *scene->objects)
            if (o->intersects(p, pDir, t0, t1))
                if (t0 < dist && !o->isLight()) shaded = true;
        
        // Given all previous parameters evaluate the local shading model and return color
        if (!shaded) color += localColor;
        
        return color / (float)bounces;
    }

    // Didn't find any object that intersects
	return glm::vec3(0.0, 0.0, 0.0);
}