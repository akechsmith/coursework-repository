#include <GL/freeglut.h>
#include <stdio.h>

// Function to draw text at given coordinates
void drawText(float x, float y, const char *text) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *text++);
    }
}

// Function to draw Cartesian plane with grid and small ticks
void drawCartesianPlane() {
    glColor3f(0.15, 0.15, 0.15);  // Light gray grid lines
    for (int i = -12; i <= 12; i++) {
        glBegin(GL_LINES);
        glVertex2i(i, -12); glVertex2i(i, 12);  // Vertical lines
        glVertex2i(-12, i); glVertex2i(12, i);  // Horizontal lines
        glEnd();
    }

    // Axes (white)
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2i(-12, 0); glVertex2i(12, 0);  // X-axis
    glVertex2i(0, -12); glVertex2i(0, 12);  // Y-axis
    glEnd();

    // Unit ticks (white)
    for (int i = -12; i <= 12; i++) {
        glBegin(GL_LINES);
        glVertex2f(i, -0.1); glVertex2f(i, 0.1);  // X-axis ticks
        glVertex2f(-0.1, i); glVertex2f(0.1, i);  // Y-axis ticks
        glEnd();
    }

    // Labels for grid numbers
    glColor3f(1.0, 1.0, 1.0);
    char label[10];
    for (int i = -12; i <= 12; i++) {
        if (i != 0) {
            sprintf(label, "%d", i);
            drawText(i - 0.3, -0.5, label);  // X-axis labels
            drawText(-0.7, i - 0.3, label);  // Y-axis labels
        }
    }

    drawText(-0.3, -0.5, "0");  // Origin
    drawText(11.5, -0.5, "X");  // X-axis title
    drawText(-0.5, 11.5, "Y");  // Y-axis title
}

// Function to draw and fill the polygon in red
void drawFilledPolygon() {
    glColor3f(1.0, 0.0, 0.0);  // Red color for the filled polygon
    glBegin(GL_POLYGON);
    glVertex2i(8, 4);
    glVertex2i(2, 4);
    glVertex2i(0, 8);
    glVertex2i(3, 12);
    glVertex2i(7, 12);
    glVertex2i(10, 8);
    glEnd();

    // Labeling the vertices
    drawText(8, 4, "(8,4)");
    drawText(2, 4, "(2,4)");
    drawText(0, 8, "(0,8)");
    drawText(3, 12, "(3,12)");
    drawText(7, 12, "(7,12)");
    drawText(10, 8, "(10,8)");
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCartesianPlane();
    drawFilledPolygon();
    glFlush();
}

// Initialize OpenGL
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-12.5, 12.5, -12.5, 12.5);
}

// Main function
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Q4ai: Filled Polygon");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

