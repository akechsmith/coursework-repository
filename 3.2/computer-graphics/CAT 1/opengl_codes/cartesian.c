#include <GL/freeglut.h>
#include <stdio.h>

void drawText(float x, float y, const char *text) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *text++);
    }
}

void drawCartesianPlane() {
    // Grid lines (very light gray)
    glColor3f(0.15, 0.15, 0.15);
    for(int i = -12; i <= 12; i++) {
        glBegin(GL_LINES);
        glVertex2i(i, -12); glVertex2i(i, 12);   // Vertical
        glVertex2i(-12, i); glVertex2i(12, i);   // Horizontal
        glEnd();
    }

    // Axes (bright white)
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2i(-12, 0); glVertex2i(12, 0);      // X-axis
    glVertex2i(0, -12); glVertex2i(0, 12);      // Y-axis
    glEnd();

    // Unit ticks (white)
    for(int i = -12; i <= 12; i++) {
        glBegin(GL_LINES);
        glVertex2f(i, -0.1); glVertex2f(i, 0.1);   // X-ticks
        glVertex2f(-0.1, i); glVertex2f(0.1, i);   // Y-ticks
        glEnd();
    }

    // Labels
    glColor3f(1.0, 1.0, 1.0);
    char label[10];
    for(int i = -12; i <= 12; i++) {
        if(i != 0) {
            sprintf(label, "%d", i);
            drawText(i - 0.3, -0.5, label);      // X-labels
            drawText(-0.7, i - 0.3, label);      // Y-labels
        }
    }
    drawText(-0.3, -0.5, "0");                   // Origin
    drawText(11.5, -0.5, "X");                   // X-title
    drawText(-0.5, 11.5, "Y");                   // Y-title
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCartesianPlane();
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-12.5, 12.5, -12.5, 12.5);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Subtle Grid Cartesian Plane");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}