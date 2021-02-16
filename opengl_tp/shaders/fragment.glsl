#version 330 core

out vec4 frag_color;

in vec2 texture_coordinate;
in vec3 vertex_coordinate;

uniform float time;
uniform sampler2D texture1;

void main(){
    //frag_color = texture(texture1, texture_coordinate);
    frag_color = vec4(vertex_coordinate+0.5, 1);
}
