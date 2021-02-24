#version 330 core
layout (location = 0) in vec3 aVertexCoord;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
out vec3 vertexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aVertexCoord, 1.0);
	ourColor = aColor;
	vertexCoord = aVertexCoord;
}