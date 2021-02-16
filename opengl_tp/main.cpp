#include "include/glad/glad.h"
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include "include/stb/stb_image.h"
#include <GLFW/glfw3.h>

#include "shader.hpp"

int window_size[2] = {800, 600};

void resize_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
    window_size[0] = width;
    window_size[1] = height;
}

void process_input(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(window_size[0], window_size[1], "TP Opengl", NULL, NULL);
    if(window == NULL){
        std::cerr << "Error creating GLFW windows" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Error loading GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, resize_callback);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, 0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, 0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, 0.5f,  1.0f, 1.0f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3,
        4, 5, 6,
        5, 6, 7,
        2, 6, 7,
        3, 2, 7,
        3, 7, 5,
        1, 3, 5,
        0, 4, 6,
        2, 6, 0,
    };

    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *img_data = stbi_load("img/peppers.png", &width, &height, &channels, 0);
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
    stbi_image_free(img_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    shader.use();
    shader.set_int("texture1", 0);
    float rotation = 0;

    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(window)){
        process_input(window);

        glClearColor(255.0f, 255.0f, 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)window_size[0]/(float)window_size[1], 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(glm::vec3(5.0f, 3.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 model = glm::mat4(1.0f);

        //model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
        //model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        rotation += 0.5;

        glm::mat4 mvp = projection*view*model;
        shader.set_mat4("mvp", mvp);

        shader.set_float("time", glfwGetTime());

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}