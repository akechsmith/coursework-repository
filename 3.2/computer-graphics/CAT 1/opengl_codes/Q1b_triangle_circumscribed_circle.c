#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>

#define BUFFER_SIZE 50
#define LABEL_OFFSET 0.5

// Global variables for circumcircle
float circ_x = 0, circ_y = 0, circ_r = 0;
float view_left, view_right, view_bottom, view_top;

void drawText(float x, float y, const char *text) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *text++);
    }
}

void drawCartesianPlane() {
    // Draw grid lines
    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_LINES);
    for(float i = floor(view_left); i <= ceil(view_right); i += 1.0f) {
        glVertex2f(i, view_bottom);
        glVertex2f(i, view_top);
    }
    for(float i = floor(view_bottom); i <= ceil(view_top); i += 1.0f) {
        glVertex2f(view_left, i);
        glVertex2f(view_right, i);
    }
    glEnd();

    // Draw axes
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(view_left, 0); glVertex2f(view_right, 0);  // X-axis
    glVertex2f(0, view_bottom); glVertex2f(0, view_top);    // Y-axis
    glEnd();

    // Axis labels
    char label[BUFFER_SIZE];
    glColor3f(1.0, 1.0, 1.0);
    
    // X-axis labels
    for(float i = floor(view_left); i <= ceil(view_right); i += 1.0f) {
        if(fabs(i) > 0.1) {  // Skip origin
            snprintf(label, BUFFER_SIZE, "%.0f", i);
            drawText(i - LABEL_OFFSET/2, -LABEL_OFFSET, label);
        }
    }
    
    // Y-axis labels
    for(float i = floor(view_bottom); i <= ceil(view_top); i += 1.0f) {
        if(fabs(i) > 0.1) {  // Skip origin
            snprintf(label, BUFFER_SIZE, "%.0f", i);
            drawText(-LABEL_OFFSET, i - LABEL_OFFSET/2, label);
        }
    }
    
    // Origin label
    drawText(-LABEL_OFFSET, -LABEL_OFFSET, "0");
}

void drawTriangle() {
    // Triangle vertices
    float vertices[3][2] = {{-1,6}, {2,0}, {-4,9}};
    
    // Draw triangle
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
    for(int i = 0; i < 3; i++) {
        glVertex2fv(vertices[i]);
    }
    glEnd();

    // Label vertices
    glColor3f(1.0, 1.0, 1.0);
    char label[BUFFER_SIZE];
    for(int i = 0; i < 3; i++) {
        snprintf(label, BUFFER_SIZE, "(%.0f,%.0f)", 
                vertices[i][0], vertices[i][1]);
        drawText(vertices[i][0] + LABEL_OFFSET, 
                vertices[i][1] + LABEL_OFFSET, label);
    }
}

void computeCircumcircle(float x1, float y1, 
                        float x2, float y2,
                        float x3, float y3) {
    float D = 2 * (x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2));
    
    circ_x = ((x1*x1 + y1*y1)*(y2 - y3) + 
            (x2*x2 + y2*y2)*(y3 - y1) + 
            (x3*x3 + y3*y3)*(y1 - y2)) / D;
            
    circ_y = ((x1*x1 + y1*y1)*(x3 - x2) + 
            (x2*x2 + y2*y2)*(x1 - x3) + 
            (x3*x3 + y3*y3)*(x2 - x1)) / D;
            
    circ_r = sqrt(pow(x1 - circ_x, 2) + pow(y1 - circ_y, 2));
}

void drawCircumscribedCircle() {
    // Draw circle
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 360; i++) {
        float angle = i * M_PI / 180.0f;
        glVertex2f(circ_x + circ_r*cos(angle), 
                  circ_y + circ_r*sin(angle));
    }
    glEnd();

    // Label circle properties
    char label[BUFFER_SIZE];
    glColor3f(1.0, 1.0, 0.0);  // Yellow labels
    snprintf(label, BUFFER_SIZE, "Center: (%.1f, %.1f)", circ_x, circ_y);
    drawText(circ_x - circ_r/2, circ_y + circ_r + 1, label);
    
    snprintf(label, BUFFER_SIZE, "Radius: %.1f", circ_r);
    drawText(circ_x - circ_r/2, circ_y + circ_r + 2, label);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCartesianPlane();
    drawTriangle();
    drawCircumscribedCircle();
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    // Triangle vertices
    float vertices[3][2] = {{-1,6}, {2,0}, {-4,9}};
    computeCircumcircle(vertices[0][0], vertices[0][1],
                       vertices[1][0], vertices[1][1],
                       vertices[2][0], vertices[2][1]);

    // Calculate dynamic viewport
    float padding = circ_r * 0.3;
    view_left = circ_x - circ_r - padding;
    view_right = circ_x + circ_r + padding;
    view_bottom = circ_y - circ_r - padding;
    view_top = circ_y + circ_r + padding;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(view_left, view_right, view_bottom, view_top);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Q1b_triangle_circumscribed_circle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}