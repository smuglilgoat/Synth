#version 330 core
out vec4 FragColor;  
in vec3 ourColor;
in vec3 vertexCoord;
  
void main()
{
    FragColor = vec4(vertexCoord, 1.0);
}
