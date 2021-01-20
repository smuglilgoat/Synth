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
    glClear(GL_COLOR_BUFFER_BIT);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
    glutSwapBuffers();
}

void ExitFunction(int value)
{
    glDeleteBuffers(1, &VBOID);
    glDeleteVertexArrays(1, &VAOID);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(100, 100);
    glutInitContextVersion(3, 3);
    glutInitContextFlags(GLUT_CORE_PROFILE);
    __glutCreateWindowWithExit("TP4 OpenGL - GLEW", ExitFunction);

    glewExperimental = TRUE;
    if(glewInit() != GLEW_OK){
        exit(EXIT_FAILURE);
    }
    
    //glutCreateWindow("TP OpenGL");

    glGenVertexArrays(1, &VAOID);
    glBindVertexArray(VAOID);

    glGenBuffers(1, &VBOID);
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);

    static const GLfloat g_vertex_buffer_data[] = {
        // first triangle
        -0.9f, -0.5f, 0.0f,
        -0.0f, -0.5f, 0.0f,  
        -0.45f, 0.5f, 0.0f,  
        // second triangle
         0.0f, -0.5f, 0.0f,  
         0.9f, -0.5f, 0.0f, 
         0.45f, 0.5f, 0.0f   
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glutDisplayFunc(display);
    glutIdleFunc(display);
    glClearColor(220.0f/255.0f, 220.0f/255.0f , 220.0f/255.0f, 0.0f);

    glutMainLoop();
    return (0);
}
