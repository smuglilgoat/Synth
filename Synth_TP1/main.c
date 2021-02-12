#include <windows.h>
#include <GL/glut.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
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
    glClearColor(1.0f, 1.0f, 0.0f, 0.0f);
    glutMainLoop();
    return (0);
}
