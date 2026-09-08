#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <filesystem>

#include "Shader.h"
#include "Lighting.h"
#include "Camera.h"
#include "Cube.h"
#include "Scene.h"

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

Camera camera;

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

bool firstMouse = true;
void framebuffer_size_callback(GLFWwindow*, int, int);
void mouse_callback(GLFWwindow*, double, double);
void processInput(GLFWwindow*);


int main()
{

    glfwInit();


    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MAJOR,
        3
    );

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MINOR,
        3
    );
    glfwWindowHint(
        GLFW_OPENGL_PROFILE,
        GLFW_OPENGL_CORE_PROFILE
    );

    GLFWwindow* window =
        glfwCreateWindow(
            SCR_WIDTH,
            SCR_HEIGHT,
            "DUT Computer Laboratory OpenGL",
            nullptr,
            nullptr
        );

    if (!window)
    {
        std::cout << "Window creation failed\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(
        window,
        framebuffer_size_callback
    );

    glfwSetCursorPosCallback(
        window,
        mouse_callback
    );

    glfwSetInputMode(
        window,
        GLFW_CURSOR,
        GLFW_CURSOR_DISABLED
    );

    if (!gladLoadGLLoader(
        (GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD failed\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);

    glCullFace(GL_BACK);

    Shader shader(
        "assets/shaders/vertex.glsl",
        "assets/shaders/fragment.glsl"
    );

    Cube cube;
    Scene scene;
    Lighting lighting;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame =
            glfwGetTime();
        deltaTime =
            currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(
            0.15f,
            0.18f,
            0.25f,
            1.0f
        );
        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT
        );
        shader.use();
        glm::mat4 view =
            camera.GetViewMatrix();
        glm::mat4 projection =
            glm::perspective(
                glm::radians(camera.Zoom),
                (float)SCR_WIDTH / SCR_HEIGHT,
                0.1f,
                100.0f
            );

        shader.setMat4(
            "view",
            view
        );


        shader.setMat4(
            "projection",
            projection
        );

        lighting.SetViewPosition(camera.Position);
        lighting.Apply(shader);


        scene.Draw(
            shader,
            cube
        );

        glfwSwapBuffers(window);

        glfwPollEvents();

    }

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow* window)
{

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);



    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);



    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);



    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);



    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

}

void framebuffer_size_callback(
    GLFWwindow*,
    int width,
    int height)
{
    glViewport(
        0,
        0,
        width,
        height
    );
}

void mouse_callback(
    GLFWwindow*,
    double xpos,
    double ypos)
{

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }


    float xoffset = xpos - lastX;

    float yoffset = lastY - ypos;


    lastX = xpos;
    lastY = ypos;



    camera.ProcessMouseMovement(
        xoffset,
        yoffset
    );

}