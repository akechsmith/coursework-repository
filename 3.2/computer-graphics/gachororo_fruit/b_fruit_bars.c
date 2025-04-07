// ICS2311 CAT Group 7 - Fruit Preference Bar Chart (macOS Version)
// Compile with: clang -framework OpenGL -framework GLUT b_fruit_bars.c -o FruitBars

#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// Structure to hold fruit data
typedef struct {
    char name[20];
    int count;
    float color[3]; // RGB values
} FruitData;

// Global array of fruit data
FruitData fruits[] = {
    {"Avocado", 36, {0.0, 0.4, 0.0}},     // Dark green
    {"Orange", 41, {1.0, 0.5, 0.0}},      // Orange color
    {"Banana", 19, {1.0, 1.0, 0.0}},      // Yellow
    {"Kiwifruit", 28, {0.4, 0.6, 0.0}},   // Kiwi green
    {"Mangos", 30, {1.0, 0.6, 0.2}},      // Mango orange
    {"Grapes", 16, {0.5, 0.0, 0.5}}       // Purple
};

const int numFruits = sizeof(fruits) / sizeof(fruits[0]);
const int maxCount = 50;
const float barWidth = 0.8;
const float barSpacing = 0.4;

// Offset for the chart (starting point at (5,5))
const float xOffset = 5.0;
const float yOffset = 5.0;

// Function to draw text in the scene
void drawText(const char* text, float x, float y) {
    glRasterPos2f(x, y);
    for(const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }
}

void drawCoordinateSystem() {
    // Draw main axes
    glColor3f(0.5, 0.5, 0.5);
    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex2f(0.0, 0.0); glVertex2f(10.0, 0.0);
        glVertex2f(0.0, 0.0); glVertex2f(0.0, 10.0);
    glEnd();

    // Grid lines
    glColor3f(0.2, 0.2, 0.2);
    glLineWidth(1.0);
    glBegin(GL_LINES);
    for (int i = 1; i <= 10; i++) {
        glVertex2f(i, 0.0); glVertex2f(i, 10.0);
        glVertex2f(0.0, i); glVertex2f(10.0, i);
    }
    glEnd();

    // Ticks and numbers
    glColor3f(1.0, 1.0, 1.0);
    for (int i = 1; i <= 10; i++) {
        glBegin(GL_LINES);
            glVertex2f(i, -0.2); glVertex2f(i, 0.2);
            glVertex2f(-0.2, i); glVertex2f(0.2, i);
        glEnd();

        char str[10];
        sprintf(str, "%d", i);
        glRasterPos2f(i - 0.1, -0.6);
        for (char* c = str; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);

        glRasterPos2f(-0.6, i - 0.1);
        for (char* c = str; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
    }

    // Origin label
    glRasterPos2f(-0.4, -0.6);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '0');

    // Highlight (5,5)
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(8.0);
    glBegin(GL_POINTS);
        glVertex2f(xOffset, yOffset);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    drawText("(5,5) - Chart Origin", xOffset - 0.5, yOffset + 0.2);
}

float scaleValue(int value) {
    return (float)value / maxCount * 4.0;
}

void drawChartAxes() {
    glLineWidth(2.5);
    
    // x-axis - BLACK
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex2f(xOffset, yOffset);
        glVertex2f(xOffset + 8.0, yOffset);
    glEnd();
    
    // y-axis - RED
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
        glVertex2f(xOffset, yOffset);
        glVertex2f(xOffset, yOffset + 5.0);
    glEnd();
    
    // Ticks on y-axis
    glColor3f(1.0, 0.0, 0.0);
    for (int i = 0; i <= 40; i += 10) {
        float y = yOffset + scaleValue(i);
        glBegin(GL_LINES);
            glVertex2f(xOffset - 0.1, y);
            glVertex2f(xOffset + 0.1, y);
        glEnd();

        char str[10];
        sprintf(str, "%d", i);
        glRasterPos2f(xOffset - 0.5, y);
        for (char* c = str; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
    }

    // Horizontal grid lines
    glColor3f(0.3, 0.3, 0.3);
    glLineWidth(1.0);
    for (int i = 10; i <= 40; i += 10) {
        float y = yOffset + scaleValue(i);
        glBegin(GL_LINES);
            glVertex2f(xOffset, y);
            glVertex2f(xOffset + 8.0, y);
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawCoordinateSystem();
    drawChartAxes();

    glColor3f(1.0, 1.0, 1.0);
    drawText("Youth Fruit Preferences in Gachororo (Starting at 5,5)", 1.0, 9.5);
    drawText("Total Participants: 170", 1.0, 9.0);

    // X-axis label
    glColor3f(0.0, 0.0, 0.0);
    drawText("Fruit Type", xOffset + 6.0, yOffset - 0.5);

    float xPos = xOffset + 0.5;
    for (int i = 0; i < numFruits; i++) {
        float barHeight = scaleValue(fruits[i].count);

        glColor3fv(fruits[i].color);
        glBegin(GL_QUADS);
            glVertex2f(xPos, yOffset);
            glVertex2f(xPos + barWidth, yOffset);
            glVertex2f(xPos + barWidth, yOffset + barHeight);
            glVertex2f(xPos, yOffset + barHeight);
        glEnd();

        // Outline
        glColor3f(0.8, 0.8, 0.8);
        glLineWidth(1.0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(xPos, yOffset);
            glVertex2f(xPos + barWidth, yOffset);
            glVertex2f(xPos + barWidth, yOffset + barHeight);
            glVertex2f(xPos, yOffset + barHeight);
        glEnd();

        // Count label
        glColor3f(1.0, 1.0, 1.0);
        char countStr[10];
        sprintf(countStr, "%d", fruits[i].count);
        glRasterPos2f(xPos + barWidth/2 - 0.1, yOffset + barHeight + 0.3);
        for (char* c = countStr; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);

        // Rotated fruit name
        glColor3f(1.0, 1.0, 1.0);
        glPushMatrix();
        glTranslatef(xPos + barWidth / 2, yOffset - 0.1, 0);
        glRotatef(-45, 0, 0, 1);
        glRasterPos2f(-0.3, 0);
        for (char* c = fruits[i].name; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
        glPopMatrix();

        xPos += barWidth + barSpacing;
    }

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 11, -1, 11);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("ICS2311 CAT Group 7 - Fruit Chart (macOS)");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}