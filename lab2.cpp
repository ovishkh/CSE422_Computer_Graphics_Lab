#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>

float currentAngle = 0.0f;

void updateRotation(int value) {
    currentAngle += 30.0f;

    if (currentAngle > 360.0f) {
        currentAngle -= 360.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(100, updateRotation, 0);
}

void display() {
    glClearColor(0.05f, 0.05f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-300, 300, -300, 300, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glRotatef(currentAngle, 0.0f, 0.0f, 1.0f);

    glColor3f(0.0f, 0.8f, 1.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(   0.0f,  150.0f);  // top
        glVertex2f(-130.0f, -100.0f);  // bottom left
        glVertex2f( 130.0f, -100.0f);  // bottom right
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Continuous 30-Degree Rotating Triangle");

    glutDisplayFunc(display);
    glutTimerFunc(100, updateRotation, 0);

    glutMainLoop();
    return 0;
}



#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>

void bresenhams(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int x = x1, y = y1;
    int pk = 2 * dy - dx;

    glBegin(GL_POINTS);

    if (dx >= dy) {
        for (int i = 0; i <= dx; i++) {
            glVertex2i(x, y);
            if (pk >= 0) { y += sy; pk -= 2 * dx; }
            pk += 2 * dy;
            x += sx;
        }
    } else {
        pk = 2 * dx - dy;
        for (int i = 0; i <= dy; i++) {
            glVertex2i(x, y);
            if (pk >= 0) { x += sx; pk -= 2 * dy; }
            pk += 2 * dx;
            y += sy;
        }
    }

    glEnd();
}

void drawRectangle(int x1, int y1, int x2, int y2) {
    // bottom
    bresenhams(x1, y1, x2, y1);
    // top
    bresenhams(x1, y2, x2, y2);
    // left
    bresenhams(x1, y1, x1, y2);
    // right
    bresenhams(x2, y1, x2, y2);
}

void display() {
    glClearColor(0.05f, 0.05f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 600, 0, 600, -1, 1);

    glPointSize(2);

    // Rectangle 1 - yellow
    glColor3f(1.0f, 1.0f, 0.0f);
    drawRectangle(100, 150, 500, 450);

    // Rectangle 2 - cyan (inside)
    glColor3f(0.0f, 1.0f, 1.0f);
    drawRectangle(180, 220, 420, 380);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Rectangle");

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}


#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <cmath>

void drawCirclePoints(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);
    glEnd();
}

void midpointCircle(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int p = 1 - r;

    drawCirclePoints(xc, yc, x, y);

    while (x < y) {
        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
        drawCirclePoints(xc, yc, x, y);
    }
}

void fillCircle(int xc, int yc, int r) {
    glBegin(GL_LINES);
    for (int y = -r; y <= r; y++) {
        int x = (int)sqrt((double)(r * r - y * y));
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc + y);
    }
    glEnd();
}

void display() {
    glClearColor(0.05f, 0.05f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 600, 0, 600, -1, 1);

    int cx = 300, cy = 300, r = 150;

    // filled circle - sky blue
    glColor3f(0.3f, 0.7f, 1.0f);
    fillCircle(cx, cy, r);

    // border - white
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(2);
    midpointCircle(cx, cy, r);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Midpoint Circle with Border");

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
