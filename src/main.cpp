#include <iostream>
#include <GlWrapper.hpp>
#include <GL/glut.h>

using namespace flappybird;

void glWrapperTest(int *argc, char **args);
void glWrapperTestDisplay(void);
void glWrapperTestKeyboard(
    const uint8_t key, const int mouseX, const int mouseY
);
void glWrapperTestMouse(
    const int button, const int state, const int mouseX, const int mouseY
);

void glTest(int *argc, char **args);
void glTestDisplay(void);

int main(int argc, char **args) {
    //glTest(&argc, args);
    glWrapperTest(&argc, args);
    return 0;
}

void glWrapperTest(int *argc, char **args) {
    glut::init(argc, args);
    const glut::Window win(
        "GL Wrapper Test", { 640, 480 },
        { GLUT_SCREEN_WIDTH / 2 - 320, GLUT_SCREEN_HEIGHT / 2 - 240 }
    );
    win.run(glWrapperTestDisplay, glWrapperTestKeyboard, glWrapperTestMouse);
}


void glWrapperTestDisplay(void) {
    static float angle = 0.0f;
    
    gl::clear();
    
    // Reset transformations and set the camera
    gl::loadIdentity();
    gl::utility::lookAt({ 0, 0, 10 }, { 0, 0, 0 }, { 0, 1, 0 });
    
    gl::rotate(angle, { 0, 1, 0 });         // Apply rotation
    
    // Draw triangle
    gl::clear();
    gl::pushTris({
        { -2, -2, -5 },
        { 2, 0, -5 },
        { 0, 2, -5 },
    });
    gl::display();
    
    // Rotate more
    angle += 0.1f;
    
    gl::display();
}

void glWrapperTestKeyboard(
        const uint8_t key, const int mouseX, const int mouseY) {
    if(key == static_cast<uint8_t>(glut::Key::Escape)) {
        exit(0);
    }
}

void glWrapperTestMouse(
        const int button, const int state, const int mouseX, const int mouseY) {
    
}

void glTest(int *argc, char **args) {
    glutInit(argc, args);
    glutCreateWindow("GLUT Test");
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(
        GLUT_SCREEN_WIDTH / 2 - 320, GLUT_SCREEN_HEIGHT / 2 - 240
    );
    glutDisplayFunc(glTestDisplay);         // Display callback for re-paint
    glutMainLoop();
}

void glTestDisplay(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Set bg color to black
    glClear(GL_COLOR_BUFFER_BIT);           // Clear the color buffer
    
    // Draw a red 1x1 square
    glBegin(GL_QUADS);                      // Each set of 4 vertices form quad
    glColor3f(1.0f, 0.0f, 0.0f);            // red
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
    glEnd();
    
    glFlush();                              // Render now
}
