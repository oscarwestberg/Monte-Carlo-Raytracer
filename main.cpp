//
//  main.cpp
//  Monte-Carlo-Raytracer-Project
//

#include <iostream>
#include <glm/vec3.hpp>
#include <vector>

const int screenWidth = 800, screenHeight = 600;

Vec3f trace(const Vec3f &rayorig, const Vec3f &raydir,
	const std::vector<Sphere> &spheres,const int &depth){

	float tnear = INFINITY;		//if we never set tnear again, its infinite
	const Sphere* sphere = NULL;
	// find intersection of this ray with the sphere in the scene
	for (unsigned i = 0; i < spheres.size(); ++i) {
		float t0 = INFINITY, t1 = INFINITY;
		if (spheres[i].intersect(rayorig, raydir, t0, t1)) {	//for every sphere, check collision
			if (t0 < 0) t0 = t1;	// if we are inside sphere?
			if (t0 < tnear) {
				tnear = t0;
				sphere = &spheres[i];
			}
		}
	}
}

void render(const std::vector<Sphere> &spheres){
	for (unsigned y = 0; y < screenHeight; ++y) {
		for (unsigned x = 0; x < screenWidth; ++x, ++pixel) {
			//set rayDir first
			*pixel = trace(Vec3f(0), rayDir, spheres, 0);		//for each pixel, trace
		}
	}
}

int main() {
	glm::vec3 radianceArray[screenWidth * screenHeight];

	// ----------------------------------------------
	// Loop through every pixel and cast ray into scene
	// ----------------------------------------------
	for (int x = 0; x < screenWidth; x++) {
		for (int y = 0; y < screenHeight; y++) {
			// Cast ray

			// Temp value
			radianceArray[screenWidth * y + x] = glm::vec3(255, 125, 0);
		}
	}


	// ----------------------------------------------
	// Save radianceArray to file
	// ----------------------------------------------
	FILE *file = fopen("image.ppm", "w");
	fprintf(file, "P3\n%d %d\n%d\n", screenWidth, screenHeight, 255);

	for (int i = 0; i < screenWidth * screenHeight; i++)
		fprintf(file, "%i %i %i ", (int)radianceArray[i].x, (int)radianceArray[i].y, (int)radianceArray[i].z);

	std::cout << "Created file\n";


	return 0;
}
