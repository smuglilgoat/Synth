#include <windows.h>
#include <GL/glut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.75f);
    glVertex2f(-0.5f, 0.25f);
    glVertex2f(0.5f, 0.25f);
    glEnd();
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, 0.25f);
    glVertex2f(0.5f, 0.25f);
    glVertex2f(0.5f, -0.25f);
    glVertex2f(-0.5f, -0.25f);
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(320, 320);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("TP OpenGL - Une Maison");
    glutDisplayFunc(display);
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glutMainLoop();
    return (0);
}
