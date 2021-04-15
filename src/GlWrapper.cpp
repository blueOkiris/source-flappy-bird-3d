#include <string>
#include <vector>
#include <GL/glut.h>
#include <GlWrapper.hpp>

using namespace flappybird;

void glut::Window::_changeSize(const int width, const int height) {
    const auto newHeight = height == 0 ? 1 : height;
    const auto ratio = 1.0f * width / newHeight;

    glMatrixMode(GL_PROJECTION);        // Use the Projection Matrix
    glLoadIdentity();                   // Reset Matrix
    glViewport(0, 0, width, newHeight); // Set viewport to entire window
    gluPerspective(45, ratio, 1, 1000); // Set the correct perspective.
    glMatrixMode(GL_MODELVIEW);         // Get Back to the Modelview
}

glut::Window::Window(
        const std::string &title,
        const gl::Vector2i initSize, const gl::Vector2i initPos) :
        _id(glutCreateWindow(title.c_str())) {
    glutInitWindowSize(initSize.x, initSize.y);
    glutInitWindowPosition(initSize.x, initSize.y);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutReshapeFunc(glut::Window::_changeSize);
}

void glut::Window::run(
        void (*displayFunc)(void),
        void (*keyboardFunc)(const uint8_t, const int, const int),
        void (*mouseFunc)(const int, const int, const int, const int)) const {
    glutDisplayFunc(displayFunc);
    glutKeyboardFunc(keyboardFunc);
    glutMouseFunc(mouseFunc);
    glutIdleFunc(displayFunc);
    
    glutMainLoop();
}
