#include <windows.h>
#include <GL/freeglut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    glColor3f(1.0f,0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glTranslatef(2.0, 2.0, 0.0);
    glVertex2f(0,0.5);
    glVertex2f(-0.5,0);
    glVertex2f(0.5,0);
    glEnd();
    glPopMatrix();

    glBegin(GL_TRIANGLES);
    glScalef(0.5,0.5,0.5);
    glColor3f(1.0f,0.0f, 1.0f);
    glTranslatef(2.0, 2.0, 0.0);
    glVertex2f(0,0.25);
    glVertex2f(-0.25,0);
    glVertex2f(0.25,0);
    glEnd();

    glFlush();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(320, 320);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("TP OpenGL");
    glutDisplayFunc(display);
    glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 0.1, 100);
    gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
    glutMainLoop() ;
    return(0) ;
}
