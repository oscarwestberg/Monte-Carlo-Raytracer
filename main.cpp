//
//  main.cpp
//  Monte-Carlo-Raytracer-Project
//

#include <iostream>
#include <glm/vec3.hpp>

const int screenWidth = 800, screenHeight = 600;

bool intersect(const Vec3f &rayorig, const Vec3f &raydir, float &t0, float &t1) const
{
	Vec3f l = center - rayorig;
	float tca = l.dot(raydir);
	if (tca < 0) return false;
	float d2 = l.dot(l) - tca * tca;
	if (d2 > radius2) return false;
	float thc = sqrt(radius2 - d2);
	t0 = tca - thc;
	t1 = tca + thc;

	return true;
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
            radianceArray[screenWidth * y + x] = glm::vec3(255,125,0);
        }
    }
    
    
    // ----------------------------------------------
    // Save radianceArray to file
    // ----------------------------------------------
    FILE *file = fopen("image.ppm", "w");
    fprintf(file, "P3\n%d %d\n%d\n", screenWidth, screenHeight, 255);
    
    for (int i = 0; i < screenWidth * screenHeight; i++)
        fprintf(file,"%i %i %i ", (int)radianceArray[i].x, (int)radianceArray[i].y, (int)radianceArray[i].z);
    
    std::cout << "Created file\n";
    
    
    return 0;
}
