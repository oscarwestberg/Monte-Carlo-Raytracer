//
//  Ray.cpp
//  Monte-Carlo-Raytracer-Project
//

#include "Ray.hpp"
#include "Sphere.hpp"

#define INF 9999
#define M_PI 3.14159265358979323846

Ray::Ray(Scene *s) {
    scene = s;
}

glm::vec3 Ray::findRandomDirection(glm::vec3 rayOrig, float radius) {
	glm::vec3 center = scene->lightPos1;
	glm::vec3 sw = center - rayOrig;
	glm::vec3 su = glm::normalize(glm::cross((abs(sw.x)>0.1 ? glm::vec3(0, 1, 0) : glm::vec3(1, 1, 1)), sw));
	glm::vec3 sv = glm::cross(sw, su);

	float maxCosA = sqrt(1 - radius*radius / glm::dot(rayOrig - center, rayOrig - center));
	float rand1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float rand2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float cosA = 1 - rand1 + rand1 * maxCosA;
	float sinA = sqrt(1 - cosA * cosA);
	float phi = 2 * M_PI*rand2;
	glm::vec3 randomDir = su*cos(phi)*sinA + sv*sin(phi)*sinA + sw*cosA;
	glm::normalize(randomDir);

	return randomDir;
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
        
        // If the closest object is a light, return light color
        if (s->isLight())
            return s->color;
        
        // p is the point of intersection
        // pDir is a normalized vector from p towards light source
        glm::vec3 color(0.0, 0.0, 0.0);
        glm::vec3 p = rayOrig + rayDir * tNear;
        glm::vec3 pDir = scene->lightPos1 - p;
        
        float dist = glm::length(pDir);
        pDir = glm::normalize(pDir);
        
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
            
            // r is the reflected direction
            glm::vec3 r = rayDir - 2 * glm::dot(rayDir, s->getNormal(p)) * s->getNormal(p);
            
            Ray ray(scene);
            color += ray.trace(p, r, depth, bounces);
            
//            color = s->color;
        }
        
        // Material is diffuse, do Monte Carlo stuff
        else {
            // russian roulette
            // random new ray over hemisphere of normal
            
            color = s->color;
        }
        
        // Shoot shadow ray(s) to random position on light
		int shadowRays = 4;
		for (int i = 0; i < shadowRays; i++) {
			for (auto &o : *scene->objects) {
				//If we collide with a nonlight object
				if (o->intersects(p, pDir, t0, t1))
					if (t0 < dist && !o->isLight()) return glm::vec3(0.0, 0.0, 0.0);

				if (o->isLight()) {
					Sphere * s = static_cast <Sphere*>(o); 
					float r = s->getRadius();
				
					glm::vec3 pRandomDir = findRandomDirection(p,r);
					if (o->intersects(p, pRandomDir, t0, t1)) {
						//color += ;
					}
				}
			}
		}		

			// Given all previous parameters evaluate the local shading model and return color
        return color;
    }

	return glm::vec3(0.0, 0.0, 0.0);
}