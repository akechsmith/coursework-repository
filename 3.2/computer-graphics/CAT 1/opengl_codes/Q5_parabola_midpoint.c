#include <GL/freeglut.h>
#include <stdio.h>

// Function to draw text at given coordinates
void drawText(float x, float y, const char *text) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *text++);
    }
}

// Function to draw Cartesian plane
void drawCartesianPlane() {
    glColor3f(0.15, 0.15, 0.15);  // Light gray grid lines
    for (int i = -12; i <= 12; i++) {
        glBegin(GL_LINES);
        glVertex2i(i, -12); glVertex2i(i, 12);
        glVertex2i(-12, i); glVertex2i(12, i);
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
        glVertex2f(i, -0.1); glVertex2f(i, 0.1);
        glVertex2f(-0.1, i); glVertex2f(0.1, i);
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

// Function to draw the parabola using the Midpoint Algorithm
void drawParabola() {
    glColor3f(1.0, 0.5, 0.0);  // Orange color for the parabola
    glPointSize(3.0);
    
    glBegin(GL_POINTS);
    
    int x = 0, y = 0;
    int p = 1 - 2 * y;  // Initial decision parameter

    // First region (when slope < 1)
    while (2 * y < 12) {  
        glVertex2i(x, y);
        glVertex2i(x, -y);  // Symmetry
        y++;

        if (p < 0) {
            p += 1 - 2 * y;
        } else {
            x++;
            p += 1 - 2 * y + 2 * x;
        }
    }

    // Second region (when slope >= 1)
    while (x < 12) {  
        glVertex2i(x, y);
        glVertex2i(x, -y);  // Symmetry
        x++;

        if (p > 0) {
            p += 1 - 2 * y + 2 * x;
        } else {
            y++;
            p += 1 - 2 * y + 2 * x;
        }
    }

    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCartesianPlane();
    drawParabola();
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
    glutCreateWindow("Q5: Midpoint Parabola Drawing");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

