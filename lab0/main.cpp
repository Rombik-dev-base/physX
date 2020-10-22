#include <iostream>
#include <GL/glut.h>
#include <cmath>

using namespace std;


void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(1);
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(-20, 0);
    glVertex2f(20, 0);
    glVertex2f(0, 20);
    glVertex2f(0, -20);
    glEnd();
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_LINE_LOOP);
    double Y0 = 1;
    double omegY = 1;
    double DeltFi = 0;
    double X0 = 1;
    double omegX = 1;
    for(float a = 0; a < 2 * M_PI; a += 0.01)
        glVertex2f(X0 * cos(omegX*a),Y0 * cos(omegY * a + DeltFi));
    glEnd();
    glFlush();
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(720,720);
    glutInitWindowPosition(720,240);
    glutCreateWindow("Drawing");
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0,20.0,-20.0,20.0,-20.0,20.0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
