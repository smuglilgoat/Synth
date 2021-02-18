#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <string.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstddef>
#include "shader_m.h"
#include "math.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
int diffX, diffY, xOld, yOld;

using namespace glm;
struct STRVertex
{
    vec3 position;
    vec3 couleur;
};

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "TP OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("D:\\Documents\\Code\\synth_tp\\synth_tp7\\shaders\\shader.vs", "D:\\Documents\\Code\\synth_tp\\synth_tp7\\shaders\\shader.fs"); // you can name your shader files however you like

    // float vertices[] = {
    //     // positions          // colors
    //     -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    //     0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    //     0.5f, 0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    //     0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
    //     -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    //     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,

    //     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    //     0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
    //     0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    //     0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    //     -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    //     -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f,

    //     -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    //     -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    //     -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    //     -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
    //     -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    //     -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,

    //     0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    //     0.5f, 0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
    //     0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    //     0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    //     0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
    //     0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f,

    //     -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
    //     0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
    //     0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
    //     0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f,
    //     -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    //     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f,

    //     -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    //     0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,
    //     0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
    //     0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
    //     -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
    //     -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f
    // };
    // unsigned int indices[] = {
    //     0, 1, 3, // first triangle
    //     1, 2, 3  // second triangle
    // };

    double pi = 3.14, x, y;
    float rayon = 2;
    int numPoints = 20;
    int indice = 1;

    STRVertex g_vertex_buffer_data[numPoints + 2];

    g_vertex_buffer_data[0] = {vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f)};

    for (int i = 0; i < numPoints; i++)
    {
        x = rayon * cos(i * 2 * pi / numPoints);
        y = rayon * sin(i * 2 * pi / numPoints);
        g_vertex_buffer_data[indice] = {vec3(x, y, 0.0f), vec3(0.0f, 0.0f, 1.0f)};
        indice++;
    }

    g_vertex_buffer_data[indice] = g_vertex_buffer_data[1];

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(STRVertex), (void *)(offsetof(STRVertex, couleur)));
    glEnableVertexAttribArray(1);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);
        
        // render
        // ------
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render the cube
        ourShader.use();

        // create transformations
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians((float) diffX), glm::vec3(0.0f, 0.0f, 1.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

        ourShader.setMat4("projection", projection);

        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 36);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLE_FAN, 0, numPoints + 2);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        //glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    diffX = xOld - xpos;
    diffY = yOld - ypos;
    glfwSwapBuffers(window);
    xOld = xpos;
    yOld = ypos;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(window);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}