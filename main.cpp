//
//  main.cpp
//  Monte-Carlo-Raytracer-Project
//

#include <iostream>
#include <math.h>
//#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "Sphere.hpp"
#include "Ray.hpp"
#include "Scene.hpp"

const int screenWidth = 800, screenHeight = 600;

int main() {
    glm::vec3 radianceArray[screenWidth * screenHeight];
    std::vector<Surface> surfaces;
    Scene scene(&surfaces);
    
    // ----------------------------------------------
    // Create the scene
    // ----------------------------------------------
    glm::vec3 colorRed(255, 0.0, 0.0);
    
    Sphere s1(glm::vec3(0.0, 1.0, -5.0), 2, colorRed);
    Sphere s2(glm::vec3(0.0, -1.0, -3.0), 1.5, colorRed);
    
    surfaces.push_back(s1);
    surfaces.push_back(s2);
    
    // ----------------------------------------------
    // Loop through every pixel and cast ray into scene
    // ----------------------------------------------
    for (int x = 0; x < screenWidth; x++) {
        for (int y = 0; y < screenHeight; y++) {
            
            // Get screen space coordiantes from normalized device coordinates
            float aspectRatio = (float)screenWidth/(float)screenHeight;
            float pixelX = (((x + 0.5) / screenWidth) * 2 - 1) * aspectRatio * tan(scene.fov/2.0);
            float pixelY = (1 - 2 * ((y + 0.5) / screenHeight)) * tan(scene.fov/2.0);
            
            // Define origin and direction
            glm::vec3 rayOrig = scene.cameraPos;
            glm::vec3 rayDir = glm::vec3(pixelX, pixelY, scene.cameraDir.z) - rayOrig;
            rayDir = glm::normalize(rayDir);
            
            // This step can be done many times
            // Shoot ray into scene
            Ray ray(&scene);
            glm::vec3 color = ray.trace(rayOrig, rayDir, 0.0, 0);
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
