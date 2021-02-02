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

using namespace std;

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path){

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::string Line = "";
		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}else{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::string Line = "";
		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}



	GLint Result = GL_FALSE;
	int InfoLogLength;



	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
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
	if ( InfoLogLength > 0 ){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
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
GLuint programID;
mat4 MVP;
GLuint MatrixID;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(programID);
    glBindBuffer(GL_ARRAY_BUFFER, VBOID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 3);
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
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    
    };  

    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    programID = LoadShaders("D:\\Documents\\Code\\synth_tp\\synth_pt5\\SimpleVertexShader.vertexshader", "D:\\Documents\\Code\\synth_tp\\synth_pt5\\SimpleFragmentShader.fragmentshader");
    mat4 Projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    mat4 View = lookAt(vec3(2,2,5),vec3(0,0,0),vec3(0,1,0) );
    mat4 Model = mat4(1.0f);
    Model = translate(Model,vec3(-1.0f, 0.0f, 0.0f));
    Model = scale(Model,vec3(2.5f, 1.5f ,1.0f));
    Model = rotate(Model,radians(45.0f),vec3(0.0f,0.0f,1.0f));

    MVP = Projection * View * Model;
    MatrixID = glGetUniformLocation(programID, "MVP");
    
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glClearColor(220.0f/255.0f, 220.0f/255.0f , 220.0f/255.0f, 0.0f);

    glutMainLoop();
    return (0);
}
