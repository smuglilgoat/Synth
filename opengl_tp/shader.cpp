#include "shader.hpp"

Shader::Shader(std::string vertex_shader_path, std::string fragment_shader_path){
    std::ifstream vertex_shader_file(vertex_shader_path);
    std::string vertex_shader_text((std::istreambuf_iterator<char>(vertex_shader_file)),
                        std::istreambuf_iterator<char>());

    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    const char* t = vertex_shader_text.c_str();
    glShaderSource(vertex_shader, 1, &t, NULL);
    glCompileShader(vertex_shader);

    int success;
    char info[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(vertex_shader, 512, NULL, info);
        std::cerr << "Error compiling vertex shader: " << info << std::endl;
        glDeleteShader(vertex_shader);
    }

    std::ifstream fragment_shader_file(fragment_shader_path);
    std::string fragment_shader_text((std::istreambuf_iterator<char>(fragment_shader_file)),
                        std::istreambuf_iterator<char>());

    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    t = fragment_shader_text.c_str();
    glShaderSource(fragment_shader, 1, &t, NULL);
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

    if(!success){
        glGetShaderInfoLog(fragment_shader, 512, NULL, info);
        std::cerr << "Error compiling fragment shader: " << info << std::endl;
        glDeleteShader(fragment_shader);
    }

    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shader_program, 512, NULL, info);
        std::cerr << "Error linking shader program: " << info << std::endl;
    }

    this->id = shader_program;
}

void Shader::use(){
    glUseProgram(this->id);
}

void Shader::set_float(std::string name, float value){
    int uniform_location = glGetUniformLocation(this->id, name.c_str());
    glUniform1f(uniform_location, value);
}

void Shader::set_int(std::string name, int value){
    int uniform_location = glGetUniformLocation(this->id, name.c_str());
    glUniform1i(uniform_location, value);
}

void Shader::set_mat4(std::string name, glm::mat4 value){
    int uniform_location = glGetUniformLocation(this->id, name.c_str());
    glUniformMatrix4fv(uniform_location, 1, GL_FALSE, glm::value_ptr(value));
}