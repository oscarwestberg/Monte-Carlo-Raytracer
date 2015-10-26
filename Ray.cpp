//
//  Ray.cpp
//  Monte-Carlo-Raytracer-Project
//

#include "Ray.hpp"
#include "Sphere.hpp"

#define INF 9999
#define M_PI 3.14159265358979323846

#include <iostream>
using namespace std;

Ray::Ray(Scene *s) {
    scene = s;
}

glm::vec3 Ray::findRandomDirection(glm::vec3 rayOrig, float radius) {
	glm::vec3 center = scene->lightPos1;
	glm::vec3 sw = glm::normalize(center - rayOrig);
	glm::vec3 su = glm::normalize(glm::cross((glm::abs(sw.x)>0.1 ? glm::vec3(0, 1, 0) : glm::vec3(1, 0, 0)), sw));
	glm::vec3 sv = glm::cross(sw, su);

	float maxCosA = sqrt(1.0f - radius*radius / glm::dot(center - rayOrig, center - rayOrig));
	float rand1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float rand2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float cosA = 1.0f - rand1 + rand1 * maxCosA;
	float sinA = sqrt(1.0f - cosA * cosA);
	float phi = 2 * M_PI*rand2;
	glm::vec3 randomDir = su*(float)(cos(phi)*sinA) + sv*(float)(sin(phi)*sinA) + sw*cosA;
	glm::normalize(randomDir);

	return randomDir;
}

glm::vec3 Ray::trace(glm::vec3 rayOrig, glm::vec3 rayDir, float depth, int bounces) {
    // Ray termination
    if (depth > scene->maxDepth || bounces > scene->maxBounces) {
        return glm::vec3(0.0, 0.0, 0.0);
    }    
    // ----------------------------------------------
	// Compare ray with every object in scene
	// Find the smallest distance to an object
    // ----------------------------------------------
	float t0, t1, tNear = INF, lightDist = INF;
    Surface *s = nullptr; // Pointer to closest object
    
	for (auto &o : *scene->objects) {
		if (o->intersects(rayOrig, rayDir, t0, t1)) {
            if (t0 < tNear) {
                tNear = t0;
                s = o;
            }
		}
	}

	
    
    // ----------------------------------------------
    // We have found an object
    // ----------------------------------------------
	if (s != nullptr) {

		// If the closest object is a light, return light color
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

		// ----------------------------------------------
		// If the object is reflective or refractive, calculate new ray(s)
		// ----------------------------------------------
		if (s->isReflective() || s->isRefractive()) {

			// If the object is refractive, create refractive ray
			// Not implemented yet
			if (s->isRefractive()) {

				// Calculate new refractive ray
				// Need to do a flip if we are inside the object
				glm::vec3 n = normal;
				const float index = 1 / 1.5;
				//                Sphere *temp = static_cast <Sphere*>(s);
				//                if (glm::length(temp->getCenter() - p) < temp->getRadius()) n = -n;

				glm::vec3 t = glm::normalize(glm::refract(rayDir, n, index));

				Ray ray(scene);
				color += ray.trace(p, t, depth, bounces);
			}

			// Calculate reflective ray for both refracive and reflective materials
			// Trace reflective ray
			Ray ray(scene);
			color += ray.trace(p, r, depth, bounces);
		}
		// ----------------------------------------------
		// Material is diffuse, do Monte Carlo stuff
		// ----------------------------------------------
		else {
			// russian roulette
			// random new ray over hemisphere of normal
			//Ray ray(scene);
			//color += ray.trace(p, normal, depth, bounces);

			// Material is diffuse - lambertian reflectance
			// We only have one light source
			float lambert = glm::dot(normal, pDir);
			localColor = s->color * lambert;
		}

		// ----------------------------------------------
		// Calculate shadow rays
		// ----------------------------------------------
		bool shaded = false;

		// Shoot shadow ray(s) to random position on light
		float shadowRays = 4;
		float shadowraysHit = 0;
		float shadowrayIntensity = 1;
		
		Surface* nearestObject;
		for (int i = 0; i < shadowRays; i++) {
			for (auto &light : *scene->objects) {
				if (light->isLight()) {
					tNear = INF;
					nearestObject = NULL;
					Sphere * s = static_cast <Sphere*>(light);
					float r = s->getRadius();
					glm::vec3 pRandomDir = findRandomDirection(p, r);

					for (auto &o : *scene->objects) {
						if (o->intersects(p, pRandomDir, t0, t1)) {
							if (t0 < tNear) {
								tNear = t0;
								nearestObject = o;
							}
						}
					}

					if (nearestObject->isLight())
						shadowraysHit++;
				}
			}
		}
		//cout << (shadowraysHit);
        // ----------------------------------------------
        // Given all previous parameters evaluate the local shading model and return color
        // ----------------------------------------------
		if (shadowraysHit > 0) {
			shaded = false;
			shadowrayIntensity = shadowraysHit / shadowRays;
		}
		else {
			shaded = true;
		}

        if (!shaded) color += shadowrayIntensity*localColor;
		else {
			color += localColor * (float)0.5;
		}
        return color / (float)bounces;
    }

    // Didn't find any object that intersects
	return glm::vec3(0.0, 0.0, 0.0);
}