#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>  

#define DEG_TO_RAD 0.0174533  

void drawText(float x, float y, const char *text) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *text++);
    }
}

void drawCartesianPlane() {
    glColor3f(0.15, 0.15, 0.15);
    for(int i = -12; i <= 12; i++) {
        glBegin(GL_LINES);
        glVertex2i(i, -12); glVertex2i(i, 12);
        glVertex2i(-12, i); glVertex2i(12, i);
        glEnd();
    }

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2i(-12, 0); glVertex2i(12, 0);
    glVertex2i(0, -12); glVertex2i(0, 12);
    glEnd();

    for(int i = -12; i <= 12; i++) {
        glBegin(GL_LINES);
        glVertex2f(i, -0.1); glVertex2f(i, 0.1);
        glVertex2f(-0.1, i); glVertex2f(0.1, i);
        glEnd();
    }

    glColor3f(1.0, 1.0, 1.0);
    char label[10];
    for(int i = -12; i <= 12; i++) {
        if(i != 0) {
            sprintf(label, "%d", i);  
            drawText(i - 0.3, -0.5, label);
            drawText(-0.7, i - 0.3, label);
        }
    }
    drawText(-0.3, -0.5, "0");
    drawText(11.5, -0.5, "X");
    drawText(-0.5, 11.5, "Y");
}

// Function to rotate a point around (cx, cy)
void rotatePoint(float cx, float cy, float *x, float *y, float angle) {
    float s = sin(angle * DEG_TO_RAD);
    float c = cos(angle * DEG_TO_RAD);
    
    // Translate point to origin
    *x -= cx;
    *y -= cy;

    // Rotate
    float newX = *x * c - *y * s;
    float newY = *x * s + *y * c;

    // Translate back
    *x = newX + cx;
    *y = newY + cy;
}

// Function to draw a filled, rotated circle
void drawRotatedFilledCircle(float xc, float yc, float r, float angle) {
    glColor3f(1.0, 0.0, 0.0);  // Red color

    glBegin(GL_POLYGON);  // Use polygon to approximate a filled circle
    for (int i = 0; i < 360; i += 5) {  
        float x = xc + r * cos(i * DEG_TO_RAD);
        float y = yc + r * sin(i * DEG_TO_RAD);
        rotatePoint(xc, yc, &x, &y, angle);  // Rotate each point
        glVertex2f(x, y);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCartesianPlane();
    
    drawRotatedFilledCircle(1, 1, 4, -60);  // Circle centered at (1,1), rotated 60°

    drawText(1, 1, "(1,1)");  // Label center
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
    glutCreateWindow("Q1ai: Rotate and Fill Circle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
