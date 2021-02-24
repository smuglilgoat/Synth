#version 330 core
out vec4 FragColor;  
in vec3 ourColor;
in vec3 ourVertex;
  
void main()
{
    FragColor = vec4(ourVertex + 0.5, 1.0);
}
