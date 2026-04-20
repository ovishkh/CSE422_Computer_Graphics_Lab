#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>

void bresenhams(int x1, int y1, int x2, int y2) {
    int pk, x, y;
    if (x1 == x2) {
        glBegin(GL_POINTS);
        for (int i = (y1 < y2 ? y1 : y2); i <= (y1 < y2 ? y2 : y1); i++) {
            glVertex2f(x1, i);
        }
        glEnd();
        return;
    }

    float m = (float)(y2 - y1) / (float)(x2 - x1);

    if (m <= 1 && m >= 0) {
        pk = (2 * (y2 - y1)) - (x2 - x1);
        x = x1; y = y1;
        glBegin(GL_POINTS);
        for (int i = 0; i < (x2 - x1); i++) {
            glVertex2f(x, y);
            if (pk < 0) { x++; pk += 2 * (y2 - y1); }
            else { x++; y++; pk += 2 * (y2 - y1) - 2 * (x2 - x1); }
        }
        glEnd();
    }
    else if (m > 1) {
        pk = (2 * (x2 - x1)) - (y2 - y1);
        x = x1; y = y1;
        glBegin(GL_POINTS);
        for (int i = 0; i < (y2 - y1); i++) {
            glVertex2f(x, y);
            if (pk < 0) { y++; pk += 2 * (x2 - x1); }
            else { x++; y++; pk += 2 * (x2 - x1) - 2 * (y2 - y1); }
        }
        glEnd();
    }
    else if (m < 0 && m >= -1) {
        pk = (2 * (y1 - y2)) - (x2 - x1);
        x = x1; y = y1;
        glBegin(GL_POINTS);
        for (int i = 0; i < (x2 - x1); i++) {
            glVertex2f(x, y);
            if (pk < 0) { x++; pk += 2 * (y1 - y2); }
            else { x++; y--; pk += 2 * (y1 - y2) - 2 * (x2 - x1); }
        }
        glEnd();
    }
    else {
        pk = (2 * (x2 - x1)) - (y1 - y2);
        x = x1; y = y1;
        glBegin(GL_POINTS);
        for (int i = 0; i < (y1 - y2); i++) {
            glVertex2f(x, y);
            if (pk < 0) { y--; pk += 2 * (x2 - x1); }
            else { x++; y--; pk += 2 * (x2 - x1) - 2 * (y1 - y2); }
        }
        glEnd();
    }
}

void display() {
    glClearColor(0.05f, 0.05f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 600, 0, 600, -1, 1);

    glPointSize(4);
    glEnable(GL_POINT_SMOOTH);

    glColor3f(1, 1, 0);
    bresenhams(100, 200, 300, 400);

    glColor3f(0, 1, 1);
    bresenhams(300, 400, 500, 200);

    glColor3f(1, 0, 1);
    bresenhams(100, 200, 500, 200);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Triangle - Windows Version");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}


#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include <cmath>

void drawSemicirclePoints(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glEnd();
}

void midpointCircle(int xc, int yc, int r) {
    int x = 0;
    int y = r;
    int p = 1 - r;

    drawSemicirclePoints(xc, yc, x, y);

    while (x < y) {
        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
        drawSemicirclePoints(xc, yc, x, y);
    }
}

void fillSemicircle(int xc, int yc, int r) {
    glColor3f(0.75f, 0.88f, 0.88f);
    glBegin(GL_LINES);
    for (int y = 0; y <= r; y++) {
        int x = (int)sqrt((double)(r * r - y * y));
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc + y);
    }
    glEnd();
}

void drawBase(int xc, int yc, int r) {
    glBegin(GL_LINES);
    glVertex2i(xc - r, yc);
    glVertex2i(xc + r, yc);
    glEnd();
}

void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 600, 0, 600, -1, 1);

    int centerX = 300, centerY = 200, radius = 150;

    fillSemicircle(centerX, centerY, radius);

    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(2);
    midpointCircle(centerX, centerY, radius);
    drawBase(centerX, centerY, radius);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Midpoint Semicircle with Border");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}


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

    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-100.0f, -50.0f);
        glVertex2f( 100.0f, -50.0f);
        glVertex2f( 100.0f,  50.0f);
        glVertex2f(-100.0f,  50.0f);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Continuous 30-Degree Rotating Rectangle");

    glutDisplayFunc(display);
    glutTimerFunc(100, updateRotation, 0);

    glutMainLoop();
    return 0;
}
