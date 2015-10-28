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

glm::vec3 Ray::trace(glm::vec3 rayOrig, glm::vec3 rayDir, float depth, int bounces) {
    
    // Ray termination
    if (depth > scene->maxDepth || bounces > scene->maxBounces) {
        return glm::vec3(0.0, 0.0, 0.0);
    }
    
    
    // ----------------------------------------------
	// Compare ray with every object in scene
	// Find the smallest distance to an object
    // ----------------------------------------------
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
    
    // ----------------------------------------------
    // We have found an object
    // ----------------------------------------------
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
        
        // ----------------------------------------------
        // If the object is reflective or refractive, calculate new ray(s)
        // ----------------------------------------------
        if (s->isReflective() || s->isRefractive()) {
                       
            // Calculate values used for determining refractive ray from air to glass
			glm::vec3 incident = rayDir;
			float n1 = 1.0f;
			float n2 = 1.4f;
			glm::vec3 n = s->getNormal(p);
            float index = n1/n2;
			float cos1 = glm::dot(incident, -n);
			float cos2 = sqrt(1.0f - index*index *(1.0f - cos1*cos1));
			float sinT2 = index*index * (1.0f - cos1*cos1);

			// Calculate refractive ray direction
			glm::vec3 refractDir = index*incident + (float)(index*cos1 - cos2)*n;
			
			// Calculate point of exit from Sphere
			Sphere * sphereHit = static_cast <Sphere*>(s);
			glm::vec3 sphereCenter = sphereHit->getCenter();
			// Create vector to center
			glm::vec3 pToCenter = sphereCenter - p;
			// Get distance to exit by using the projection formula
			// New point is startpoint + new direction * new distance
			glm::vec3 exitPoint = p + (2.0f * glm::dot(pToCenter, refractDir))*refractDir;

			// Calculate values used for determining refractive ray from glass to air
			incident = refractDir;
			n = - s->getNormal(exitPoint);
			index = n2 / n1;
			cos1 = glm::dot(incident, -n);
			cos2 = sqrt(1.0f - index*index *(1.0f - cos1*cos1));

			// Calculate new refractive ray direction
			refractDir = index*incident + (float)(index*cos1 - cos2)*n;
	
			// Set value R based on object material
			float R;
			if (s->isReflective() || sinT2 > 1.0f) {
				R = 1.0f;
			}
			else {
				float r0 = pow((n1 - n2) / (n1 + n2), 2);
				R = r0 + (1.0f - r0)*(pow((1.0f - cos1), 5));
			}
			float r01 = (float)rand() / RAND_MAX;

			// Create new ray
			Ray ray(scene);
			if (r01 < R) {
				// Reflection. For all reflective objects and for some rays at refractive objects
				color += ray.trace(p, r, depth, bounces);
			}
			else {
				// Refraction, only for refractive objects
				color += ray.trace(exitPoint, refractDir, depth, bounces);
			}
        }
        // ----------------------------------------------
        // Material is diffuse, do Monte Carlo stuff
        // ----------------------------------------------
        else {
            // Russian roulette
            float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            
            // Ray is scattered
            if (r1 > 0.8) {
                float inclination = (M_PI * 2 * r1);
                float azimuth = (acos(sqrt(r2)));
                glm::vec3 tangent = glm::normalize(glm::cross(normal, normal + glm::vec3(1.0)));
                
                // New random direction over hemisphere
                glm::vec3 newDir = normal;
                if (normal.y > 0) tangent.z = std::abs(tangent.z);
                
                // Rotate direction around itself and its tangent
                newDir = glm::rotate(newDir, inclination, tangent);
                newDir = glm::rotate(newDir, azimuth, normal);
                
                // Add BRDF & divide by pdf
                Ray ray(scene);
                color += ray.trace(p, newDir, 0, 0);
            }
            // Ray is absorbed
            else {
                float lambert = glm::dot(normal, pDir);
                localColor += lambert * s->color;
            }
        }
        
        // ----------------------------------------------
        // Calculate shadow rays
        // ----------------------------------------------
        bool shaded = false;
        
        // Shoot shadow ray(s) to random position on light (not random not though)
        // Does not account for any sphere that is a light at the moment
        for (auto &o : *scene->objects)
            if (o->intersects(p, pDir, t0, t1))
                if (t0 < dist && !o->isLight()) shaded = true;
        
        // ----------------------------------------------
        // Given all previous parameters evaluate the local shading model and return color
        // ----------------------------------------------
        if (!shaded) color += localColor;
        else color += localColor * (float)0.3;
        
        return color / (float)bounces;
    }

    // Didn't find any object that intersects
	return glm::vec3(0.0, 0.0, 0.0);
}