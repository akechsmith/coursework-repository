// ICS2311 CAT Group 7 - Fruit Preference Bar Chart (macOS Version)
// Compile with: clang -framework OpenGL -framework GLUT a_fruit_bars.c -o FruitBars

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
const int maxCount = 50; // Max value for y-axis (slightly more than our max data point)
const float barWidth = 1.0;
const float barSpacing = 0.5;

void drawCoordinateSystem() {
    // Draw main axes only
    glColor3f(0.5, 0.5, 0.5);  // Gray color for axes
    glLineWidth(2.0);
    glBegin(GL_LINES);
        // x-axis
        glVertex2f(0.0, 0.0);
        glVertex2f(10.0, 0.0);
        // y-axis
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, 10.0);
    glEnd();
}

// Function to draw text in the scene
void drawText(const char* text, float x, float y) {
    glRasterPos2f(x, y);
    for(const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
    }
}

// Function to scale fruit counts to fit in the display window
float scaleValue(int value) {
    // Scale to range 0 to 8 (to fit in our coordinate system)
    return (float)value / maxCount * 8.0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw coordinate system (just the axes)
    drawCoordinateSystem();

    // Draw chart title
    glColor3f(1.0, 1.0, 1.0);  // White text
    drawText("Youth Fruit Preferences in Gachororo", 1.0, 9.5);
    drawText("Total Participants: 170", 1.0, 9.0);
    
    // Draw x-axis label in BLACK as specified
    glColor3f(0.0, 0.0, 0.0);  // Black text for x-axis
    drawText("Fruit Type", 8.0, 0.5);
    
    // Starting position for first bar (in positive quadrant)
    float xPos = 1.0;
    
    // Draw bars
    for(int i = 0; i < numFruits; i++) {
        // Calculate bar height based on data
        float barHeight = scaleValue(fruits[i].count);
        
        // Draw the bar with fruit color
        glColor3fv(fruits[i].color);
        glBegin(GL_QUADS);
            glVertex2f(xPos, 0.0);
            glVertex2f(xPos + barWidth, 0.0);
            glVertex2f(xPos + barWidth, barHeight);
            glVertex2f(xPos, barHeight);
        glEnd();
        
        // Draw bar outline
        glColor3f(0.8, 0.8, 0.8);  // Light gray outline
        glLineWidth(1.0);
        glBegin(GL_LINE_LOOP);
            glVertex2f(xPos, 0.0);
            glVertex2f(xPos + barWidth, 0.0);
            glVertex2f(xPos + barWidth, barHeight);
            glVertex2f(xPos, barHeight);
        glEnd();
        
        // Draw the fruit name below the bar in BLACK as specified
        glColor3f(0.0, 0.0, 0.0);  // Black text for fruit names
        glPushMatrix();
        glTranslatef(xPos + barWidth/2, -0.1, 0);
        glRotatef(-45, 0, 0, 1); // Rotate 45 degrees counterclockwise
        glRasterPos2f(-0.3, 0);
        for(char* c = fruits[i].name; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
        }
        glPopMatrix();
        
        // Draw the count value above the bar
        char countStr[10];
        sprintf(countStr, "%d", fruits[i].count);
        glColor3f(1.0, 1.0, 1.0);  // White for count numbers
        glRasterPos2f(xPos + barWidth/2 - 0.1, barHeight + 0.3);
        for(char* c = countStr; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
        }
        
        // Move to next bar position
        xPos += barWidth + barSpacing;
    }

    // Draw y-axis scale in RED - only show meaningful values
    glColor3f(1.0, 0.0, 0.0);  // Red for y-axis scale
    for(int i = 0; i <= 40; i += 10) {
        float y = scaleValue(i);
        
        // Label the value in RED
        char str[10];
        sprintf(str, "%d", i);
        glRasterPos2f(-0.5, y - 0.1);
        for(char* c = str; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
        }
    }

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 11, -1, 11);  // Coordinate system focused on positive quadrant
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