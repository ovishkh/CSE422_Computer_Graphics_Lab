#include <windows.h>
#include <GL/glut.h>

void display()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    glOrtho(-10, 10, -10, 10, -1, 1);

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-4.0f, 2.0f);
        glVertex2f( 4.0f, 2.0f);
        glVertex2f( 0.0f, 6.0f);
    glEnd();

    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-4.0f, -4.0f);
        glVertex2f( 4.0f, -4.0f);
        glVertex2f( 4.0f,  2.0f);
        glVertex2f(-4.0f,  2.0f);
    glEnd();

    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-1.0f, -4.0f);
        glVertex2f( 1.0f, -4.0f);
        glVertex2f( 1.0f, -1.0f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-3.0f, -2.0f);
        glVertex2f(-2.0f, -2.0f);
        glVertex2f(-2.0f,  0.0f);
        glVertex2f(-3.0f,  0.0f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f( 2.0f, -2.0f);
        glVertex2f( 3.0f, -2.0f);
        glVertex2f( 3.0f,  0.0f);
        glVertex2f( 2.0f,  0.0f);
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("House");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
