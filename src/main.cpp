#include <iostream>
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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
    
    // Allow special key capture
    glfwSetInputMode(win, GLFW_STICKY_KEYS, GL_TRUE);
    
    do {
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Draw nothing
        
        glfwSwapBuffers(win);
        glfwPollEvents();
    } while(
        glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS
        && !glfwWindowShouldClose(win)
    );
}
