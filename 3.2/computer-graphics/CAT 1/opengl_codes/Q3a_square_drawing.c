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

    // Unit ticks (white) - Including the small perpendicular ticks
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

// Function to draw a square using green lines 
void drawSquare() {
    glColor3f(0.0, 1.0, 0.0);  // Green square outline
    glBegin(GL_LINE_LOOP);
    glVertex2i(0, 4);  // A
    glVertex2i(4, 4);  // B
    glVertex2i(4, 0);  // C
    glVertex2i(0, 0);  // D
    glEnd();

    // Labeling the vertices
    drawText(0, 4, "A(0,4)");
    drawText(4, 4, "B(4,4)");
    drawText(4, 0, "C(4,0)");
    drawText(0, 0, "D(0,0)");
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCartesianPlane();
    drawSquare();
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
    glutCreateWindow("Q3a: Square Drawing");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
