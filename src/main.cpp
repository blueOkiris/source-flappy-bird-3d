#include <iostream>

// shader function
#include <fstream>
#include <sstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <GlWrapper.hpp>

using namespace flappybird;

void basicWindowTest(void);

int main(int argc, char **args) {
    basicWindowTest();
    return 0;
}

void basicWindowTest(void) {
    glewExperimental = true;
    if(!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        exit(-1);
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);    // 4x antialiasing
    
    // Open gl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Open a window and create the opengl context
    auto win = glfwCreateWindow(640, 480, "Basic Window Test", NULL, NULL);
    if(!win) {
        std::cerr << "Failed to create GLFW Window." << std::endl;
        glfwTerminate();
        exit(-2);
    }
    glfwMakeContextCurrent(win);
    
    glewExperimental = true;
    if(glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW!" << std::endl;
        exit(-3);
    }
    
    // Create vertex array object
    uint vertexArrayId;
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);
    
    // Create a triangle array
    static const float vertexBufferData[] = {
        -1, -1, 0,
        1, -1, 0,
        0,  1, 0,
    };
    
    // Create triangle buffer
    uint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(
        GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData,
        GL_STATIC_DRAW
    );
    
    // Allow special key capture
    glfwSetInputMode(win, GLFW_STICKY_KEYS, GL_TRUE);
    
    // Load shaders
    const auto progId = gl::loadShaders(
        "shaders/test/testshader.vertexshader",
        "shaders/test/testshader.fragmentshader"
    );
    
    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Use shader
        glUseProgram(progId);
        
        // Vertex attribute buffer
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(
            0,                          // Matches shader
            3,                          // Size
            GL_FLOAT,                   // Type
            GL_FALSE,                   // not normalized
            0,                          // stride
            nullptr                     // Array buffer offset
        );
        
        // Draw triangle vertices starting at 0 with 3 total
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
        
        glfwSwapBuffers(win);
        glfwPollEvents();
    } while(
        glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS
        && !glfwWindowShouldClose(win)
    );
}
