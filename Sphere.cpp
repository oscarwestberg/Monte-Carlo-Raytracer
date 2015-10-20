//
//  Sphere.cpp
//  Monte-Carlo-Raytracer-Project
//

#include "Sphere.hpp"

// Constructor
Sphere::Sphere(glm::vec3 ce, float r, glm::vec3 co) {
    center = ce;
    radius = r;
    color = co;
};

bool Sphere::intersects(glm::vec3 rayOrig, glm::vec3 rayDir, float &t0, float &t1) {
	glm::vec3 l = center - rayOrig;
	float tca = glm::dot(l, rayDir);
	if (tca < 0) return false;
	float d2 = glm::dot(l, l) - tca * tca;
	if (d2 > radius) return false;
	float thc = sqrt(radius - d2);
	t0 = tca - thc;
	t1 = tca + thc;

	return true;
}