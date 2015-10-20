//
//  main.cpp
//  Monte-Carlo-Raytracer-Project
//

#include <iostream>
#include <glm/vec3.hpp>
#include "Sphere.hpp"
#include "Ray.hpp"

const int screenWidth = 800, screenHeight = 600;

int main() {
    glm::vec3 radianceArray[screenWidth * screenHeight];
    std::vector<Surface> surfaces;
    
    // ----------------------------------------------
    // Create the scene
    // ----------------------------------------------
    glm::vec3 colorRed(255, 0.0, 0.0);
    
    Sphere s1(glm::vec3(0.0, 1.0, 0.0), 2, colorRed);
    Sphere s2(glm::vec3(0.0, -1.0, 0.0), 1.5, colorRed);
    
    surfaces.push_back(s1);
    surfaces.push_back(s2);
    
    // ----------------------------------------------
    // Loop through every pixel and cast ray into scene
    // ----------------------------------------------
    for (int x = 0; x < screenWidth; x++) {
        for (int y = 0; y < screenHeight; y++) {
            // Create ray
            // Shoot ray into scene
            Ray ray(&surfaces);
            glm::vec3 rayOrig;
            glm::vec3 rayDir;
            float depth = 0;
            
            glm::vec3 color = ray.trace(rayOrig, rayDir, depth);
            
            // Temp value
            radianceArray[screenWidth * y + x] = color;
        }
    }
    
    
    // ----------------------------------------------
    // Save radianceArray to file
    // ----------------------------------------------
    FILE *file = fopen("../image.ppm", "w");
    fprintf(file, "P3\n%d %d\n%d\n", screenWidth, screenHeight, 255);
    
    for (int i = 0; i < screenWidth * screenHeight; i++)
        fprintf(file,"%i %i %i ", (int)radianceArray[i].x, (int)radianceArray[i].y, (int)radianceArray[i].z);
    
    std::cout << "Created file\n";
    
    
    return 0;
}
