#include <windows.h>
#include <GL/glut.h>
#include <math.h>

#diamond_using_dda_line

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glOrtho(0, 500, 0, 500, 0, 500);
    glClear(GL_COLOR_BUFFER_BIT);

    float x1 = 20, y1 = 20, x2 = 400, y2 = 400;

    float x3 = 400, y3 = 400, x4 = 20, y4 = 20;

    float x5 = 400, y5 = 400, x6 = 20, y6 = 20;

    float x = 400, y3 = 400, x4 = 20, y4 = 20;



    

    float xdif = x2 - x1;
    float ydif = y2 - y1;

    float xdif = x3 - x2;
    float ydif = y3 - y2;

    int steps = 0;

    if (fabs(xdif) > fabs(ydif))
    {
        steps = fabs(xdif);
    }

    
    else
    {
        steps = fabs(ydif);
    }

    float xinc = xdif / steps;
    float yinc = ydif / steps;

    int x = x1;
    int y = y1;

    glPointSize(2.0);


    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);

    for (int i = 0; i < steps;i++)
    {
        glVertex2f(x, y);
        x = x + xinc;
        y = y + yinc;
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("DDA D");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
