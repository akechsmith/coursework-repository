#define GL_SILENCE_DEPRECATION // Suppress OpenGL deprecation warnings

#include <GLUT/glut.h> // macOS-specific GLUT header
#include <iostream>

using namespace std;

// Bresenham's Line Algorithm
void bresenhamLine(int x0, int y0, int x1, int y1) {
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

    int d = 2 * dy - dx;
    int dE = 2 * dy;
    int dNE = 2 * (dy - dx);

    int x = x0, y = y0;

    glBegin(GL_POINTS);
    while (x <= x1) {
        if (steep) {
            glVertex2i(y, x); // Swap x and y for steep lines
        } else {
            glVertex2i(x, y);
        }

        if (d <= 0) {
            d += dE;
        } else {
            d += dNE;
            y += (y1 > y0 ? 1 : -1); // Handle positive and negative slopes
        }
        x++;
    }
    glEnd();
    glFlush();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // Set line color to white
    glPointSize(2.0); // Increase point size for better visibility
    bresenhamLine(1, 5, 2, 8); // Draw line from (1, 5) to (2, 8)
}

// Initialization function
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color to black
    gluOrtho2D(0, 10, 0, 10);         // Set coordinate system
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bresenham's Line Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
