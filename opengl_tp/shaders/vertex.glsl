#version 330 core

out vec2 texture_coordinate;
out vec3 vertex_coordinate;

layout (location = 0) in vec3 a_vertex_coordinate;
layout (location = 1) in vec2 a_texture_coordinate;

uniform mat4 mvp;

void main(){
    gl_Position = mvp*vec4(a_vertex_coordinate, 1.0);
    texture_coordinate = a_texture_coordinate;
    vertex_coordinate = a_vertex_coordinate;
}
