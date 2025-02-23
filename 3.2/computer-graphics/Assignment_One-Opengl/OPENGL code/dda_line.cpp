#define GL_SILENCE_DEPRECATION // Suppress OpenGL deprecation warnings

#include <GLUT/glut.h> // macOS-specific GLUT header
#include <iostream>
#include <cmath>

using namespace std;

// DDA Line Algorithm
void ddaLine(float x0, float y0, float x1, float y1) {
    float dx = x1 - x0;
    float dy = y1 - y0;

    int S;
    if (abs(dx) > abs(dy)) {
        S = abs(dx);
    } else {
        S = abs(dy);
    }

    float I_x = dx / S;
    float I_y = dy / S;

    float x = x0;
    float y = y0;

    glBegin(GL_POINTS);
    for (int i = 0; i <= S; i++) {
        glVertex2i(round(x), round(y));
        x += I_x;
        y += I_y;
    }
    glEnd();
    glFlush();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // Set line color to white
    glPointSize(2.0); // Increase point size for better visibility
    ddaLine(5, 2, 10, 3); // Draw line from (5, 2) to (10, 3)
}

// Initialization function
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    gluOrtho2D(0, 15, 0, 5);         // Set coordinate system
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("DDA Line Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
