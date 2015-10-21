//
//  main.cpp
//  Monte-Carlo-Raytracer-Project
//

#ifdef _WIN32
    #define _CRT_SECURE_NO_DEPRECATE
#endif

#include <iostream>
#include <math.h>
#include <glm/glm.hpp>
#include "Sphere.hpp"
#include "Plane.hpp"
#include "Ray.hpp"
#include "Scene.hpp"


const int screenWidth = 800, screenHeight = 600;

int main() {
    std::vector<glm::vec3> radianceArray;
    std::vector<Surface*> surfaces;
    Scene scene(&surfaces);
    
    // ----------------------------------------------
    // Create the scene
    // ----------------------------------------------
    glm::vec3 colorRed(255.0, 0.0, 0.0);
    glm::vec3 colorGreen(0.0, 255.0, 0.0);
    
    Sphere s1(glm::vec3(1.0, 1.0, -5.0), 1, colorRed);
    Sphere s2(glm::vec3(-1.0, 0.0, -8.0), 1.5, colorGreen);
    
    Plane p1(glm::vec3(0.0, 0.0, -1.0), glm::vec3(20.0, 20.0, 20.0), glm::vec3(0.0, 0.0, -10));
    Plane p2(glm::vec3(0.0, -1.0, 0.0), glm::vec3(50.0, 50.0, 50.0), glm::vec3(0.0, -5.0, 0.0));
    Plane p3(glm::vec3(0.0, 1.0, 0.0), glm::vec3(100.0, 100.0, 100.0), glm::vec3(0.0, 5.0, 0.0));
    Plane p4(glm::vec3(1.0, 0.0, 0.0), glm::vec3(150.0, 150.0, 150.0), glm::vec3(5.0, 0.0, 0.0));
    Plane p5(glm::vec3(-1.0, 0.0, 0.0), glm::vec3(200.0, 200.0, 200.0), glm::vec3(-5.0, 0.0, 0.0));
    
    surfaces.push_back(&s1);
    surfaces.push_back(&s2);
    surfaces.push_back(&p1);
    surfaces.push_back(&p2);
    surfaces.push_back(&p3);
    surfaces.push_back(&p4);
    surfaces.push_back(&p5);
    
    // ----------------------------------------------
    // Loop through every pixel and cast ray into scene
    // ----------------------------------------------
    for (int y = 0; y < screenHeight; y++) {
        for (int x = 0; x < screenWidth; x++) {
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
            radianceArray.push_back(color);
        }
    }
    
    // ----------------------------------------------
    // Save radianceArray to file
    // ----------------------------------------------
    FILE *file = fopen("../image.ppm", "w");
    fprintf(file, "P3\n%d %d\n%d\n", screenWidth, screenHeight, 255);
    
    for (int i = 0; i < screenWidth * screenHeight; i++)
        fprintf(file," %i %i %i", (int)radianceArray.at(i).x, (int)radianceArray.at(i).y, (int)radianceArray.at(i).z);
    
    std::cout << "Created file\n";
    
    
    return 0;
}
