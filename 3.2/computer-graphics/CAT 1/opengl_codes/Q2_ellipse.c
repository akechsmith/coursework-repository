#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

#define CENTER_X 2   // Ellipse center X
#define CENTER_Y -1  // Ellipse center Y
#define RX 6         // Semi-major axis (horizontal)
#define RY 5         // Semi-minor axis (vertical)

// Function to draw text labels
void drawText(float x, float y, const char *text) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *text++);
    }
}

// Function to draw the Cartesian plane with ticks
void drawCartesianPlane() {
    glColor3f(0.15, 0.15, 0.15); // Light gray grid
    for(int i = -12; i <= 12; i++) {
        glBegin(GL_LINES);
        glVertex2i(i, -12); glVertex2i(i, 12);  // Vertical grid
        glVertex2i(-12, i); glVertex2i(12, i);  // Horizontal grid
        glEnd();
    }

    // Axes (bright white)
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2i(-12, 0); glVertex2i(12, 0);  // X-axis
    glVertex2i(0, -12); glVertex2i(0, 12);  // Y-axis
    glEnd();

    // Unit ticks (perpendicular dashes)
    for (int i = -12; i <= 12; i++) {
        glBegin(GL_LINES);
        glVertex2f(i, -0.2); glVertex2f(i, 0.2);  // X-axis ticks
        glVertex2f(-0.2, i); glVertex2f(0.2, i);  // Y-axis ticks
        glEnd();
    }

    // Labels
    glColor3f(1.0, 1.0, 1.0);
    char label[10];
    for(int i = -12; i <= 12; i++) {
        if(i != 0) {
            sprintf(label, "%d", i);
            drawText(i - 0.3, -0.5, label);  // X-labels
            drawText(-0.7, i - 0.3, label);  // Y-labels
        }
    }
    drawText(-0.3, -0.5, "0");  // Origin
    drawText(11.5, -0.5, "X");  // X-title
    drawText(-0.5, 11.5, "Y");  // Y-title
}

// Function to plot symmetric ellipse points
void plotEllipsePoints(int xc, int yc, int x, int y) {
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
}

// Function to draw ellipse using Midpoint Algorithm
void drawMidpointEllipse(int xc, int yc, int rx, int ry) {
    int x = 0, y = ry;
    float dx = 2 * ry * ry * x;
    float dy = 2 * rx * rx * y;
    float d1 = ry * ry - (rx * rx * ry) + (0.25 * rx * rx);

    // Region 1
    glBegin(GL_POINTS);
    while (dx < dy) {
        plotEllipsePoints(xc, yc, x, y);
        x++;
        dx += 2 * ry * ry;
        if (d1 < 0) {
            d1 += dx + ry * ry;
        } else {
            y--;
            dy -= 2 * rx * rx;
            d1 += dx - dy + ry * ry;
        }
    }

    // Region 2
    float d2 = ry * ry * (x + 0.5) * (x + 0.5) + rx * rx * (y - 1) * (y - 1) - rx * rx * ry * ry;
    while (y >= 0) {
        plotEllipsePoints(xc, yc, x, y);
        y--;
        dy -= 2 * rx * rx;
        if (d2 > 0) {
            d2 += rx * rx - dy;
        } else {
            x++;
            dx += 2 * ry * ry;
            d2 += dx - dy + rx * rx;
        }
    }
    glEnd();
}

// Function to fill the ellipse
void fillEllipse(int xc, int yc, int rx, int ry) {
    glColor3f(1.0, 0.65, 0.0); // Orange color (#FFA500)
    glBegin(GL_POLYGON);
    for (int angle = 0; angle < 360; angle++) {
        float rad = angle * M_PI / 180;
        float x = xc + rx * cos(rad);
        float y = yc + ry * sin(rad);
        glVertex2f(x, y);
    }
    glEnd();
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCartesianPlane();

    // Fill the ellipse
    fillEllipse(CENTER_X, CENTER_Y, RX, RY);

    // Draw the ellipse outline
    glColor3f(1.0, 1.0, 1.0); // White outline
    drawMidpointEllipse(CENTER_X, CENTER_Y, RX, RY);

    // Label ellipse center
    drawText(CENTER_X, CENTER_Y, "(2,-1)");

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
    glutCreateWindow("Q2: Midpoint Ellipse Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
