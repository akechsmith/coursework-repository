#include <GL/freeglut.h>
#include <stdio.h>

// Function to draw text at given coordinates
void drawText(float x, float y, const char *text) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *text++);
    }
}

// Function to draw the Cartesian plane
void drawCartesianPlane() {
    glColor3f(0.15, 0.15, 0.15);

    // Draw grid lines
    for (int i = -12; i <= 12; i++) {
        glBegin(GL_LINES);
        glVertex2i(i, -12); glVertex2i(i, 12);  // Vertical grid lines
        glVertex2i(-12, i); glVertex2i(12, i);  // Horizontal grid lines
        glEnd();
    }

    // Draw X and Y axes
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2i(-12, 0); glVertex2i(12, 0);  // X-axis
    glVertex2i(0, -12); glVertex2i(0, 12);  // Y-axis
    glEnd();

    // Draw small tick marks on axes
    for (int i = -12; i <= 12; i++) {
        glBegin(GL_LINES);
        glVertex2f(i, -0.1); glVertex2f(i, 0.1);  // X-axis ticks
        glVertex2f(-0.1, i); glVertex2f(0.1, i);  // Y-axis ticks
        glEnd();
    }

    // Draw axis labels
    char label[10];
    for (int i = -12; i <= 12; i++) {
        if (i != 0) {
            sprintf(label, "%d", i);
            drawText(i - 0.3, -0.5, label);  // X-axis labels
            drawText(-0.7, i - 0.3, label);  // Y-axis labels
        }
    }

    // Origin and axis labels
    drawText(-0.3, -0.5, "0");
    drawText(11.5, -0.5, "X");
    drawText(-0.5, 11.5, "Y");
}

// Function to draw a circle using Bresenham's algorithm
void drawBresenhamCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;

    glBegin(GL_POINTS);
    while (x <= y) {
        // Plot all symmetric points
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);

        // Update decision parameter
        x++;
        if (d > 0) {
            y--;
            d += 4 * (x - y) + 10;
        } else {
            d += 4 * x + 6;
        }
    }
    glEnd();
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCartesianPlane();

    // Draw the circle in light blue
    glColor3f(0.0, 1.0, 1.0);
    drawBresenhamCircle(1, 1, 4);

    // Label the circle center
    drawText(1, 1, "(1,1)");

    glFlush();
}

// Initialization function
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Set background color to black
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-12.5, 12.5, -12.5, 12.5);  // Set 2D orthographic projection
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Q1ai: Bresenham Circle");
    
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
