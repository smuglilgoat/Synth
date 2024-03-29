#include <windows.h>
#include <GL/glut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);
    glRotatef(90, 0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0, 0.5);
    glVertex2f(-0.5, 0);
    glVertex2f(0.5, 0);
    glScalef(0.5, 0.5, 0.5);
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex2f(0, 0.25);
    glVertex2f(-0.25, 0);
    glVertex2f(0.25, 0);
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(320, 320);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("TP OpenGL");
    glutDisplayFunc(display);
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    glutMainLoop();
    return (0);
}
