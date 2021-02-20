#define GLEW_STATIC

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <math.h>

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

struct STRVertex
{
	vec3 position;
	vec3 couleur;
};

GLuint VAOID;
GLuint VBOID;
GLuint programID;
GLuint MatrixID;
GLuint IBOID;
mat4 MVP;
mat4 View;
mat4 Model;
mat4 Projection;
float zoom = 2.0f;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(programID);
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	glEnableVertexAttribArray(0);
	// Draw the shape
	//glVertexAttribPointer(glEnableVertexAttribArray(index), elements_to_take, type, normalized , step, first_element_offset);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)0);
	//Color the shape
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *)(sizeof(float) * 3));
	//glDrawArrays(mode,first_element, size_g_vertex_buffer_data);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 102);
	glDisableVertexAttribArray(0);
	glutSwapBuffers();
}

void KeyPressed(unsigned char touche, int x, int y)
{
	float step = 0.05f;
	switch (touche)
	{
	case 'w':
		zoom = zoom + step;
		break;
	case 's':
		zoom = zoom - step;
		break;
	case 27: //ESC
		exit(0);
		break;
	default:
		glClearColor(0.6f, 0.6f, 0.6f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	View = lookAt(vec3(zoom, zoom, zoom), vec3(0, 0, 0), vec3(0, 1, 0));
	Model = mat4(1.0f);
	Model = rotate(Model, radians(270.0f), vec3(1.0f, 0.0f, 0.0f));
	Projection = perspective(radians(45.0f), 1.0f, 0.1f, 100.0f);
	MVP = Projection * View * Model;
	MatrixID = glGetUniformLocation(programID, "MVP");
	glClear(GL_COLOR_BUFFER_BIT);
	glutPostRedisplay();
}
void ExitFunction(int value)
{
	glDeleteBuffers(1, &VBOID);
	glDeleteVertexArrays(1, &VAOID);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutInitContextVersion(3, 3);
	glutInitContextFlags(GLUT_CORE_PROFILE);
	__glutCreateWindowWithExit("TP7 Synthese d'image", ExitFunction);

	glewExperimental = TRUE;
	if (glewInit() != GLEW_OK)
	{
		exit(EXIT_FAILURE);
	}

	glGenVertexArrays(1, &VAOID);
	glBindVertexArray(VAOID);

	glGenBuffers(1, &VBOID);
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);

	double pi = 3.14f, x, y;
	float radius = 0.5f;
	float height = 0.8f;
	int numPoints = 100;
	int offset = numPoints + 2;
	float alternative = 1.0f;
	STRVertex g_vertex_buffer_data[(numPoints + 3)];

	g_vertex_buffer_data[0] = {vec3(radius, 0.0f, -height), vec3(0.0f, 0.0f, 0.0f)};
	x = radius * cos(1 * 2 * pi / numPoints);
	y = radius * sin(1 * 2 * pi / numPoints);
	g_vertex_buffer_data[1] = {vec3(x, y, height), vec3(0.0f, 0.0f, 0.0f)};
	x = radius * cos(2 * 2 * pi / numPoints);
	y = radius * sin(2 * 2 * pi / numPoints);
	g_vertex_buffer_data[2] = {vec3(x, y, -height), vec3(0.0f, 0.0f, 0.0f)};
	for (int i = 3; i < numPoints; i++)
	{
		x = radius * cos(i * 2 * pi / numPoints);
		y = radius * sin(i * 2 * pi / numPoints);
		g_vertex_buffer_data[i] = {vec3(x, y, alternative * height), vec3(0.0f, 0.0f, 0.0f)};
		alternative = -1 * alternative;
	}
	g_vertex_buffer_data[100] = g_vertex_buffer_data[1];

	// circle code ;
	// g_vertex_buffer_data[0] = {vec3(0.0f, -0.f, 0.0f), vec3(0.0f, 0.0f, 1.0f)};

	// for (int i = 0; i < numPoints; i++)
	// {
	// 	x = rayon * cos(i * 2 * pi / numPoints);
	// 	y = rayon * sin(i * 2 * pi / numPoints);
	// 	g_vertex_buffer_data[i + 1] = {vec3(x, y, -0.5f), vec3(0.0f, 0.0f, 1.0f)};
	// }
	// g_vertex_buffer_data[numPoints + 1] = {vec3(rayon, 0.0f, -0.5f), vec3(0.0f, 0.0f, 1.0f)};

	// g_vertex_buffer_data[0] = {vec3(0.0f, -0.f, 0.0f), vec3(0.0f, 0.0f, 1.0f)};

	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	//Modifier le path

	programID = LoadShaders("D:\\Documents\\Code\\synth_tp\\synth_tp7\\shaders\\SimpleVertexShader.vertexshader", "D:\\Documents\\Code\\synth_tp\\synth_tp7\\shaders\\SimpleFragmentShader.fragmentshad"); // you can name your shader files however you like

	View = lookAt(vec3(zoom, zoom, zoom), vec3(0, 0, 0), vec3(0, 1, 0));
	Model = mat4(1.0f);
	Model = rotate(Model, radians(270.0f), vec3(1.0f, 0.0f, 0.0f));
	Projection = perspective(radians(45.0f), 1.0f, 0.1f, 100.0f);

	MVP = Projection * View * Model;
	MatrixID = glGetUniformLocation(programID, "MVP");

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutKeyboardFunc(KeyPressed);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glClearColor(0.6f, 0.6f, 0.6f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glutMainLoop();
	return (0);
}
