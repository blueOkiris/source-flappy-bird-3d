#include <string>
#include <vector>
#include <GL/glut.h>
#include <GlWrapper.hpp>

using namespace flappybird;

glut::Window::Window(
        const std::string &title,
        const gl::Vector2i initSize, const gl::Vector2i initPos,
        void (*displayFunc)(void)) :
        _id(glutCreateWindow(title.c_str())) {
    glutInitWindowSize(initSize.x, initSize.y);
    glutInitWindowPosition(initSize.x, initSize.y);
    glutDisplayFunc(displayFunc);
}

void glut::Window::run(void) const {
    glutMainLoop();
}
