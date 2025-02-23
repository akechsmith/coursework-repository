#define GL_SILENCE_DEPRECATION // Suppress OpenGL deprecation warnings

#include <GLUT/glut.h> // macOS-specific GLUT header
#include <cmath>
#include <iostream>

using namespace std;

// Function to plot a pixel with intensity
void plot(int x, int y, float intensity) {
    glColor3f(intensity, intensity, intensity); // Set pixel intensity (white)
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Gupta-Sproull weighting function
float guptaSproullWeight(float distance, float width) {
    float t = distance / width;
    if (t <= 1.0) {
        return 1.0 - t;
    }
    return 0.0;
}

// Gupta-Sproull Line Algorithm
void guptaSproullLine(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    bool steep = dy > dx;

    if (steep) {
        swap(x0, y0);
        swap(x1, y1);
        swap(dx, dy);
    }

    if (x0 > x1) {
        swap(x0, x1);
        swap(y0, y1);
    }

    int x = x0;
    float y = y0;
    float m = (float)(y1 - y0) / (x1 - x0); // Slope

    // Line width for anti-aliasing
    float lineWidth = 2.0; // Increase line width for better visibility

    while (x <= x1) {
        int yInt = floor(y);
        float frac = y - yInt;

        // Calculate brightness for the two closest pixels
        float brightness1 = guptaSproullWeight(frac, lineWidth);
        float brightness2 = guptaSproullWeight(1 - frac, lineWidth);

        if (steep) {
            plot(yInt, x, brightness1);
            plot(yInt + 1, x, brightness2);
        } else {
            plot(x, yInt, brightness1);
            plot(x, yInt + 1, brightness2);
        }

        y += m;
        x++;
    }
    glFlush();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2.0); // Increase point size for better visibility
    guptaSproullLine(-2, 3, 1, 4); // Draw line from (-2, 3) to (1, 4)
}

// Initialization function
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    gluOrtho2D(-5, 5, 0, 10);         // Set coordinate system
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Gupta-Sproull Line Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

