#pragma once

#include "include/glad/glad.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include <iostream>
#include <string>
#include <fstream>

class Shader{
public:
    unsigned int id;
    Shader(std::string vertex_shader_path, std::string fragment_shader_path);
    void use();
    void set_float(std::string name, float value);
    void set_int(std::string name, int value);
    void set_mat4(std::string name, glm::mat4 value);
};