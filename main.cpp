//
//  main.cpp
//  Monte-Carlo-Raytracer-Project
//

#include <iostream>
#include <glm/vec3.hpp>

const int screenWidth = 800, screenHeight = 600;

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
