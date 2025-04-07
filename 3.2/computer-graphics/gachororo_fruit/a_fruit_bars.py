from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *
import sys

fruits = [
    {"name": "Avocado", "count": 36, "color": [0.34, 0.51, 0.01]},
    {"name": "Orange", "count": 41, "color": [1.00, 0.65, 0.00]},
    {"name": "Banana", "count": 19, "color": [0.89, 0.81, 0.34]},
    {"name": "Kiwifruit", "count": 28, "color": [0.62, 0.89, 0.31]},
    {"name": "Mangos", "count": 30, "color": [1.00, 0.78, 0.25]},
    {"name": "Grapes", "count": 16, "color": [0.50, 0.19, 0.58]}
]

num_fruits = len(fruits)
window_width, window_height = 800, 600

def reshape(width, height):
    global window_width, window_height
    window_width, window_height = width, height
    glViewport(0, 0, width, height)
    glutPostRedisplay()

def draw_text(text, x, y, r, g, b):
    glColor3f(r, g, b)
    glRasterPos2f(x, y)
    for c in text:
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ord(c))

def display():
    glClear(GL_COLOR_BUFFER_BIT)
    
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluOrtho2D(0, window_width, 0, window_height)

    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()

    # Title and subtitle
    draw_text("Youth Fruit Preferences in Gachororo", window_width / 2 - 180, window_height - 30, 0.0, 0.0, 0.0)
    draw_text("Total Participants: 170", window_width / 2 - 100, window_height - 60, 0.0, 0.0, 0.0)

    # Axes
    glColor3f(1.0, 0.0, 0.0)  # Red Y-axis
    glLineWidth(2.0)
    glBegin(GL_LINES)
    glVertex2f(50.0, 50.0)
    glVertex2f(50.0, window_height - 50.0)
    glEnd()

    glColor3f(0.0, 0.0, 0.0)  # Black X-axis
    glBegin(GL_LINES)
    glVertex2f(50.0, 50.0)
    glVertex2f(window_width - 50.0, 50.0)
    glEnd()

    draw_text("Fruit Type", window_width / 2 - 40, 20, 0.0, 0.0, 0.0)

    # Bar settings
    bar_width = (window_width - 150) / num_fruits * 0.7
    bar_spacing = (window_width - 150) / num_fruits * 0.3
    max_bar_height = window_height - 150
    start_x = 100.0

    # Draw bars
    for fruit in fruits:
        bar_height = (fruit["count"] / 50) * max_bar_height

        glColor3fv(fruit["color"])
        glBegin(GL_QUADS)
        glVertex2f(start_x, 50.0)
        glVertex2f(start_x + bar_width, 50.0)
        glVertex2f(start_x + bar_width, 50.0 + bar_height)
        glVertex2f(start_x, 50.0 + bar_height)
        glEnd()

        # Draw value
        draw_text(str(fruit["count"]), start_x + bar_width / 2 - 10, 60 + bar_height, 0.0, 0.0, 0.0)

        # Draw fruit name (rotated)
        glPushMatrix()
        glTranslatef(start_x + bar_width / 2, 30, 0)
        glRotatef(45, 0, 0, 1)
        draw_text(fruit["name"], 0, 0, 0.0, 0.0, 0.0)
        glPopMatrix()

        start_x += bar_width + bar_spacing

    # Draw y-axis labels
    for i in range(0, 51, 10):
        y = 50 + (i / 50) * max_bar_height
        glColor3f(1.0, 0.0, 0.0)
        glBegin(GL_LINES)
        glVertex2f(45, y)
        glVertex2f(50, y)
        glEnd()
        draw_text(str(i), 30, y - 5, 1.0, 0.0, 0.0)

    glFlush()

def init():
    glClearColor(1.0, 1.0, 1.0, 1.0)

def main():
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowSize(window_width, window_height)
    glutCreateWindow(b"ICS2311 Group 7: Fruit Preference Survey")
    glutReshapeFunc(reshape)
    glutDisplayFunc(display)
    init()
    glutMainLoop()

if __name__ == "__main__":
    main()
