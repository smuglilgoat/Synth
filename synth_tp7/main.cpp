#define GLEW_STATIC

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <stdlib.h>
#include <string.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstddef>
#include "shader.hpp"
#include "math.h"

int diffX, diffY, xOld, yOld;

using namespace std;

GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path)
{

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if (VertexShaderStream.is_open())
    {
        std::string Line = "";
        while (getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    }
    else
    {
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
        getchar();
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if (FragmentShaderStream.is_open())
    {
        std::string Line = "";
        while (getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const *VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }

    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const *FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }

    // Link the program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}
using namespace glm;

GLuint VAOID;
GLuint VBOID;
GLuint IBO;

GLuint programID;
mat4 MVP;
GLuint MatrixID;

mat4 Projection;
mat4 Model;
mat4 View;

int numPoints = 20;

struct STRVertex
{
    vec3 position;
    vec3 couleur;
};

void ExitFunction(int value)
{
    glDeleteBuffers(1, &VBOID);
    glDeleteVertexArrays(1, &VAOID);
}

void MouseMotion(int x, int y)
{
    diffX = xOld - x;
    diffY = yOld - y;
    glutPostRedisplay();
    xOld = x;
    yOld = y;
}

void KeyPressed(unsigned char touche, int x, int y)
{
    switch (touche)
    {
    case 'r':
        glClearColor(1.0f, 0.0f, 0.0f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);
        break;
    case 'b':
        glClearColor(0.0f, 0.0f, 1.0f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);
        break;
    case 'v':
        glClearColor(0.0f, 1.0f, 0.0f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);
        break;
    case 27: /* Escape */
        exit(0);
        break;
    default:
        glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    glutPostRedisplay(); /// cette instruction va forcer glut à rafraîchir l’affichage.
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(programID);

    Model = rotate(Model, radians(float(diffX)), vec3(0.0f, 0.0f, 1.0f));
    //
    MVP = Projection * View * Model;

    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

    glBindVertexArray(VAOID);
    //  glDrawArrays(GL_TRIANGLES, 0, 18);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLE_FAN, 0, numPoints + 2);
    glBindVertexArray(0);

    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(80, 100);
    glutInitContextVersion(3, 3);
    glutInitContextFlags(GLUT_CORE_PROFILE);
    __glutCreateWindowWithExit("TP OpenGL", ExitFunction);
    glewExperimental = TRUE;
    if (glewInit())
    {
        cerr << "Unable to initialize GLEW ... exiting" << endl;
        exit(EXIT_FAILURE);
    }

    glGenVertexArrays(1, &VAOID);
    glBindVertexArray(VAOID);
    glGenBuffers(1, &VBOID);
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);

    ////
    double pi = 3.14, x, y;
    float rayon = 2;

    int indice = 1;

    STRVertex g_vertex_buffer_data[numPoints + 2];

    g_vertex_buffer_data[0] = {vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f)};

    for (int i = 0; i < numPoints; i++)
    {
        x = rayon * cos(i * 2 * pi / numPoints);
        y = rayon * sin(i * 2 * pi / numPoints);
        g_vertex_buffer_data[indice] = {vec3(x, y, 0.0f), vec3(0.0f, 0.0f, 1.0f)};
        indice++;
    }

    g_vertex_buffer_data[indice] = g_vertex_buffer_data[1];

    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36*sizeof(unsigned int), vertex_index,GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(STRVertex), (void *)(offsetof(STRVertex, couleur)));

    glBindVertexArray(0);
    programID = LoadShaders("D:\\Documents\\Code\\synth_tp\\synth_tp7\\SimpleVertexShader.vertexshader", "D:\\Documents\\Code\\synth_tp\\synth_tp7\\SimpleFragmentShader.fragmentshader");

    Projection = perspective(90.0f, 600.0f / 600.0f, 0.1f, 100.0f);
    View = lookAt(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 1, 0));
    Model = mat4(1.0f);
    //        Model = translate(Model,vec3(-1.0f, 0.0f, 0.0f));
    //        Model = scale(Model,vec3(2.5f, 1.0f ,1.0f));
    //Model = rotate(Model,radians(45.0f),vec3(0.0f,0.0f,1.0f));
    //
    MVP = Projection * View * Model;
    MatrixID = glGetUniformLocation(programID, "MVP");
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glutDisplayFunc(display);
    glutKeyboardFunc(KeyPressed);
    glutMotionFunc(MouseMotion);

    glutMainLoop();
    return (0);
}
