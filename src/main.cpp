#include <iostream>
#include <GL/glut.h>

void glTest(int *argc, char **argv);
void glTestDisplay(void);

int main(int argc, char **argv) {
    glTest(&argc, argv);
    return 0;
}

void glTest(int *argc, char **argv) {
    glutInit(argc, argv);
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
