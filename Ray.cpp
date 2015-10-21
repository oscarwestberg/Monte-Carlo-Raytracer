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
	glm::vec3 c(0.0, 0.0, 255.0);

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
    
    if (s != nullptr) {
        return s->color;
    }
    
//	glm::vec3 intersectPos = rayOrig + nearestIntersection*rayDir;
	// If we found an intersection, cast shadow ray
	// Compare shadow ray with every object
	//Ray ray(&scene);
	//rayDir = scene->lightPos1 - intersectPos;
	//glm::vec3 color = ray.trace(intersectPos, rayDir, 0.0, 0);

	// If point isn't in shadow, update with object's color and light's brightness



	return c;
}