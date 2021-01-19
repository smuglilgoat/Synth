#define GLEW_STATIC

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

GLuint VAOID;
GLuint VBOID;

void display()
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glutSwapBuffers();
}

void ExitFunction(int value)
{
    glDeleteBuffers(1, &VBOID);
    glDeleteVertexArrays(1, &VAOID);
}

int main(int argc, char **argv)
{
    glewExperimental = TRUE;
    glewInit();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE); //glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(100, 100);

    glutInitContextVersion(3, 3);
    glutInitContextFlags(GLUT_CORE_PROFILE);
    __glutCreateWindowWithExit("TP OpenGL", ExitFunction);

    glGenVertexArrays(1, &VAOID);
    glBindVertexArray(VAOID);
    glGenBuffers(1, &VBOID);
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);

    static const GLfloat g_vertex_buffer_data[] = {
        1.0f,
        0.0f,
        0.0f,
        0.0f,
        1.0f,
        0.0f,
        -1.0f,
        0.0f,
        0.0f,
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glutDisplayFunc(display);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glutMainLoop();
    return (0);
}
