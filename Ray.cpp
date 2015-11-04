//
//  Ray.cpp
//  Monte-Carlo-Raytracer-Project
//

#include "Ray.hpp"
#include <algorithm>

#define INF 9999
#define M_PI 3.14159265358979323846


Ray::Ray(Scene *s) {
    scene = s;
}

float OrenNayarBRDF(glm::vec3 lightDir, glm::vec3 eyeDir, glm::vec3 normal) {
    
    float roughness = 1.0;
    roughness *= roughness;
    
    float NdotL = glm::dot(normal, lightDir);
    float NdotV = glm::dot(normal, eyeDir);
    
    // Inclination angles
    float inclinationi = acos(NdotV);
    float inclinationr = acos(NdotL);
    
    float alpha = std::max(inclinationi, inclinationr);
    float beta = std::min(inclinationi, inclinationr);
    
    // Used for azimuth angle
    float gamma = glm::dot(eyeDir - normal * glm::dot(eyeDir, normal), lightDir - normal * glm::dot(lightDir, normal));
    
    float A = 1.0 - 0.5 * (roughness / (roughness + 0.57));
    float B = 0.45 * (roughness / (roughness + 0.09));
    
    return  std::max(0.0f, NdotL) * (A + B * std::max(0.0f, gamma) * sin(alpha) * tan(beta));
}
    
glm::vec3 findRandomDirection(glm::vec3 rayOrig, Sphere* light) {
	glm::vec3 center = light->getCenter();
	glm::vec3 sw = glm::normalize(center - rayOrig);
	glm::vec3 su = glm::normalize(glm::cross((glm::abs(sw.x) > 0.1 ? glm::vec3(0, 1, 0) : glm::vec3(1, 0, 0)), sw));
	glm::vec3 sv = glm::cross(sw, su);

    float radius = light->getRadius();
	float maxCosA = sqrt(1.0f - radius * radius / glm::dot(center - rayOrig, center - rayOrig));
	float rand1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float rand2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float cosA = 1.0f - rand1 + rand1 * maxCosA;
	float sinA = sqrt(1.0f - cosA * cosA);
	float phi = 2 * M_PI * rand2;
    
	glm::vec3 randomDir = su * (float)(cos(phi) * sinA) + sv * (float)(sin(phi) * sinA) + sw * cosA;
	return glm::normalize(randomDir);
}

glm::vec3 Ray::trace(glm::vec3 rayOrig, glm::vec3 rayDir, float depth, int bounces) {

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
        glm::vec3 directIllumination (0.0);
        glm::vec3 indirectIllumination (0.0);
        
        glm::vec3 p = rayOrig + rayDir * tNear;
        glm::vec3 normal = s->getNormal(p);
        glm::vec3 r = rayDir - 2 * glm::dot(rayDir, normal) * normal; // reflected direction
        
        // ----------------------------------------------
        // Indirect illumination
        // If the object is reflective or refractive, calculate new ray(s)
        // ----------------------------------------------
        if (s->isRefractive()) {
            
            // If the object is refractive, create refractive ray
            // Calculate new refractive ray
            // Need to do a flip if we are inside the object
            //glm::vec3 n = normal;
            //const float index = 1/1.5;
            //Sphere *temp = static_cast <Sphere*>(s);
            //if (glm::length(temp->getCenter() - p) < temp->getRadius()) n = -n;
            
            //glm::vec3 t = glm::normalize(glm::refract(rayDir, n, index));
            
            Ray ray(scene);
            //indirectIllumination += ray.trace(p, t, depth, bounces);
         
            // Calculate reflective ray for both refracive and reflective materials
            // Trace reflective ray
            indirectIllumination += ray.trace(p, r, depth, bounces++);
            indirectIllumination /= (float)bounces;
        }
        
        // ----------------------------------------------
        // Indirect illumination
        // Material is diffuse, do Monte Carlo stuff
        // ----------------------------------------------
        else if(bounces < scene->maxBounces) {
            // Russian roulette
            float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            float absorption = 0.5;
            
            // Ray is scattered
            if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) > absorption) {

                // New random direction over hemisphere
                float inclination = 2.0 * M_PI * r1;
                float azimuth = acos(2.0 * r2 - 1.0);
                float u = cos(azimuth);
                
                float x	= sqrt(1 - u * u) * cos(inclination);
                float y	= sqrt(1 - u * u) * sin(inclination);
                float z	= u;
                
                // New direction. If it points the wrong way, change direction
                glm::vec3 newDir(x, y, z);
                if (glm::dot(normal, newDir) < 0) newDir = -newDir;
                
                // pdf  - over hemisphere
                // cos  - relationship between normal and the direction reflected light will come from
                // BRDF - Lambertian or Oren-Nayar
                float pdf = 1.0 / 2.0 * M_PI;
                float cos = glm::dot(normal, newDir);
                float BRDF = s->isOren() ? OrenNayarBRDF(newDir, glm::normalize(-scene->cameraDir), normal) : glm::dot(normal, newDir);
                
                Ray ray(scene);
                
                indirectIllumination = ray.trace(p, newDir, depth, bounces++) * cos * BRDF / pdf;
                indirectIllumination /= ((1 - absorption));
            }
        }
        
        // ----------------------------------------------
        // Direct illumination
        // Calculate shadow rays
        // ----------------------------------------------
        int shadowRays = 4;
        
        for (int i = 0; i < scene->lights->size(); i++) {
            Sphere *l = scene->lights->at(i); // Pointer to current light
            glm::vec3 tempColor(0.0); // Total color per light
            float unobstructedRays = 0.0;
            
            for (int j = 0; j < shadowRays; j++) {
                bool shaded = false;
                glm::vec3 pDir = findRandomDirection(p, l); // Vector towards light
                float dist = glm::length(pDir);
                pDir = glm::normalize(pDir);

                // Shoot shadow ray(s) to random position on light (not random now though)
                for (auto &o : *scene->objects)
                    if (o->intersects(p, pDir, t0, t1))
                        if (t0 < dist && !o->isLight()) shaded = true;
                
                if (!shaded) {
                    unobstructedRays++;
                    float lightIntensity = 2.2 * 1.0/255.0;
                    float BRDF = s->isOren() ? OrenNayarBRDF(pDir, glm::normalize(-scene->cameraDir), normal) : glm::dot(normal, pDir);
                    // TODO: N(light) must be calculated properly
                    // radianceTransfer = dot(N(object), shadowRay) * dot(N(light), -shadowRay)
                    float radianceTransfer = glm::dot(normal, pDir) * glm::dot(-pDir, -pDir);
                    float pdfk = 2.0 * M_PI * l->getRadius() * l->getRadius(); // pdf over sphere (lights are halved spheres)
                    float pdfyk = 0.5; // Chance to pick one of the light sources
                    
                    // Direct illumination = light * BRDF * radiance transfer / pdfk * pdfyk
                    tempColor += l->color * lightIntensity * BRDF * radianceTransfer / (pdfk * pdfyk) * s->color;
                }
            }

            directIllumination += tempColor * (1.0f/(float)shadowRays);
        }

        // ----------------------------------------------
        // Add direct and indirect light and return color
        // ----------------------------------------------
        return (indirectIllumination * 2.0 + directIllumination / M_PI);
    }

    // Didn't find any object that intersects
	return glm::vec3(0.0, 0.0, 0.0);
}