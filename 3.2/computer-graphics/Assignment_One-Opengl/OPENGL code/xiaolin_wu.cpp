#define GL_SILENCE_DEPRECATION // Suppress OpenGL deprecation warnings

#include <GLUT/glut.h> // macOS-specific GLUT header
#include <iostream>
#include <cmath>

using namespace std;

// Function to plot a pixel with intensity
void plot(float x, float y, float intensity) {
    glColor3f(intensity, intensity, intensity); // Set pixel intensity (white)
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

// Xiaolin Wu's Line Algorithm
void drawLine(float x0, float y0, float x1, float y1) {
    bool steep = abs(y1 - y0) > abs(x1 - x0);

    if (steep) {
        swap(x0, y0);
        swap(x1, y1);
    }

    if (x0 > x1) {
        swap(x0, x1);
        swap(y0, y1);
    }

    float dx = x1 - x0;
    float dy = y1 - y0;
    float gradient = dy / dx;

    float y = y0;
    for (int x = x0; x <= x1; x++) {
        if (steep) {
            plot(y, x, 1 - (y - floor(y))); // Primary pixel
            plot(y + 1, x, y - floor(y));   // Secondary pixel
        } else {
            plot(x, y, 1 - (y - floor(y))); // Primary pixel
            plot(x, y + 1, y - floor(y));   // Secondary pixel
        }
        y += gradient;
    }
}

// Display function
void display() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw a thicker and more visible line
    glPointSize(2.0); // Increase point size for better visibility
    drawLine(1, 1, 3, 5); // Draw line from (1, 1) to (3, 5)

    glFlush();
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Xiaolin Wu's Line Algorithm");

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 10, 0, 10);

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
