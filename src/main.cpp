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
#include "Chair.h"

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;


// =====================================================
// GLOBAL CAMERA
// =====================================================

Camera camera;


// =====================================================
// TIMING
// =====================================================

float deltaTime = 0.0f;
float lastFrame = 0.0f;


// =====================================================
// MOUSE
// =====================================================

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;

bool firstMouse = true;


// =====================================================
// WINDOW KEY STATE
// =====================================================

bool oKeyWasPressed = false;

// =====================================================
// DOOR KEY STATE
// =====================================================

bool eKeyWasPressed = false;


// =====================================================
// FUNCTION DECLARATIONS
// =====================================================

void framebuffer_size_callback(
    GLFWwindow* window,
    int width,
    int height
);

void mouse_callback(
    GLFWwindow* window,
    double xpos,
    double ypos
);

void processInput(
    GLFWwindow* window,
    Scene& scene
);


// =====================================================
// MAIN
// =====================================================

int main()
{
    // -------------------------------------------------
    // INITIALIZE GLFW
    // -------------------------------------------------

    if (!glfwInit())
    {
        std::cout << "GLFW initialization failed\n";
        return -1;
    }


    // -------------------------------------------------
    // OPENGL VERSION
    // -------------------------------------------------

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


    // -------------------------------------------------
    // CREATE WINDOW
    // -------------------------------------------------

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


    // -------------------------------------------------
    // MAKE OPENGL CONTEXT CURRENT
    // -------------------------------------------------

    glfwMakeContextCurrent(window);


    // -------------------------------------------------
    // FRAMEBUFFER CALLBACK
    // -------------------------------------------------

    glfwSetFramebufferSizeCallback(
        window,
        framebuffer_size_callback
    );


    // -------------------------------------------------
    // MOUSE CALLBACK
    // -------------------------------------------------

    glfwSetCursorPosCallback(
        window,
        mouse_callback
    );


    // -------------------------------------------------
    // DISABLE MOUSE CURSOR
    // -------------------------------------------------

    glfwSetInputMode(
        window,
        GLFW_CURSOR,
        GLFW_CURSOR_DISABLED
    );


    // -------------------------------------------------
    // INITIALIZE GLAD
    // -------------------------------------------------

    if (!gladLoadGLLoader(
        (GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "GLAD failed\n";

        glfwDestroyWindow(window);
        glfwTerminate();

        return -1;
    }


    // -------------------------------------------------
    // OPENGL SETTINGS
    // -------------------------------------------------

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);

    glCullFace(GL_BACK);


    // -------------------------------------------------
    // ENABLE TRANSPARENCY
    // -------------------------------------------------

    glEnable(GL_BLEND);

    glBlendFunc(
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA
    );


    // -------------------------------------------------
    // SHADER
    // -------------------------------------------------

    Shader shader(
        "assets/shaders/vertex.glsl",
        "assets/shaders/fragment.glsl"
    );


    // -------------------------------------------------
    // CREATE OBJECTS
    // -------------------------------------------------

    Cube cube;

    Scene scene;

    Lighting lighting;


    // =================================================
    // MAIN RENDER LOOP
    // =================================================

    std::cout << "\n======================================================\n"
              << " DUT Computer Lab - Wheelchair Accessibility Controls:\n"
              << " [T]       : Toggle Wheelchair Transfer Mode\n"
              << " [Z] / [X] : Flip Armrests Up / Down (0 to 90 deg for lateral transfer)\n"
              << " [R] / [F] : Raise / Lower Seat Height (Pneumatic Lift)\n"
              << " [B]       : Toggle Caster Wheel Safety Brakes\n"
              << "======================================================\n\n";

    while (!glfwWindowShouldClose(window))
    {
        // -------------------------------------------------
        // CALCULATE DELTA TIME
        // -------------------------------------------------

        float currentFrame =
            static_cast<float>(glfwGetTime());

        deltaTime =
            currentFrame - lastFrame;

        lastFrame = currentFrame;


        // -------------------------------------------------
        // PROCESS INPUT
        // -------------------------------------------------

        processInput(
            window,
            scene
        );


        // -------------------------------------------------
        // UPDATE SCENE
        // -------------------------------------------------

        scene.Update(deltaTime);


        // -------------------------------------------------
        // CLEAR SCREEN
        // -------------------------------------------------

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


        // -------------------------------------------------
        // USE SHADER
        // -------------------------------------------------

        shader.use();


        // -------------------------------------------------
        // CAMERA VIEW
        // -------------------------------------------------

        glm::mat4 view =
            camera.GetViewMatrix();


        // -------------------------------------------------
        // PROJECTION
        // -------------------------------------------------

        glm::mat4 projection =
            glm::perspective(
                glm::radians(camera.Zoom),
                static_cast<float>(SCR_WIDTH) /
                static_cast<float>(SCR_HEIGHT),
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


        // -------------------------------------------------
        // LIGHTING
        // -------------------------------------------------

        lighting.SetViewPosition(
            camera.Position
        );

        lighting.Apply(shader);


        // -------------------------------------------------
        // DRAW SCENE
        // -------------------------------------------------

        scene.Draw(
            shader,
            cube
        );


        // -------------------------------------------------
        // SWAP BUFFERS
        // -------------------------------------------------

        glfwSwapBuffers(window);


        // -------------------------------------------------
        // PROCESS GLFW EVENTS
        // -------------------------------------------------

        glfwPollEvents();
    }


    // =================================================
    // CLEANUP
    // =================================================

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}


// =====================================================
// INPUT
// =====================================================

void processInput(
    GLFWwindow* window,
    Scene& scene
)
{
    // -------------------------------------------------
    // ESCAPE
    // -------------------------------------------------

    if (glfwGetKey(
        window,
        GLFW_KEY_ESCAPE
    ) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(
            window,
            true
        );
    }


    // -------------------------------------------------
    // MOVE FORWARD
    // -------------------------------------------------

    if (glfwGetKey(
        window,
        GLFW_KEY_W
    ) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(
            FORWARD,
            deltaTime
        );
    }


    // -------------------------------------------------
    // MOVE BACKWARD
    // -------------------------------------------------

    if (glfwGetKey(
        window,
        GLFW_KEY_S
    ) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(
            BACKWARD,
            deltaTime
        );
    }


    // -------------------------------------------------
    // MOVE LEFT
    // -------------------------------------------------

    if (glfwGetKey(
        window,
        GLFW_KEY_A
    ) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(
            LEFT,
            deltaTime
        );
    }


    // -------------------------------------------------
    // MOVE RIGHT
    // -------------------------------------------------

    if (glfwGetKey(
        window,
        GLFW_KEY_D
    ) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(
            RIGHT,
            deltaTime
        );
    }


    // =================================================
    // WINDOW OPEN / CLOSE
    // =================================================

    bool oKeyPressed =
        glfwGetKey(
            window,
            GLFW_KEY_O
        ) == GLFW_PRESS;


    // Only toggle once per key press.
    //
    // Without this check, holding O would rapidly
    // open and close the window every frame.

    if (oKeyPressed && !oKeyWasPressed)
    {
        scene.ToggleWindow();
    }


    oKeyWasPressed =
        oKeyPressed;

    // =================================================
// DOOR OPEN / CLOSE
// =================================================

    bool eKeyPressed =
        glfwGetKey(
            window,
            GLFW_KEY_E
        ) == GLFW_PRESS;

    // Only toggle once per key press.
    // Press E once = open.
    // Press E again = close.

    if (eKeyPressed && !eKeyWasPressed)
    {
        scene.ToggleDoor();
    }

    eKeyWasPressed =
        eKeyPressed;
    // =================================================
    // WHEELCHAIR ACCESSIBILITY CONTROLS
    // =================================================
    Chair* chair = scene.GetChair();
    if (chair)
    {
        // [T]: Toggle Wheelchair Accessible Transfer Mode
        static bool tWasPressed = false;
        bool tPressed = (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS);
        if (tPressed && !tWasPressed)
        {
            chair->ToggleWheelchairAccessibleMode();
            std::cout << "[Wheelchair Mode]: " 
                      << (chair->IsWheelchairAccessibleMode() 
                            ? "ENABLED (Armrests flipped up 90 deg, level transfer height, wheel safety brakes locked)" 
                            : "DISABLED (Standard seating)") 
                      << std::endl;
        }
        tWasPressed = tPressed;

        // [B]: Toggle Caster Wheel Safety Brakes
        static bool bWasPressed = false;
        bool bPressed = (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS);
        if (bPressed && !bWasPressed)
        {
            chair->SetWheelsLocked(!chair->AreWheelsLocked());
            std::cout << "[Wheel Brakes]: " 
                      << (chair->AreWheelsLocked() ? "LOCKED (Transfer Safe)" : "UNLOCKED (Rolling)") 
                      << std::endl;
        }
        bWasPressed = bPressed;

        // [R] / [F]: Pneumatic Seat Height Adjust (Level transfer matching wheelchair cushion)
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        {
            chair->SetSeatHeightOffset(chair->GetSeatHeightOffset() + 0.08f * deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        {
            chair->SetSeatHeightOffset(chair->GetSeatHeightOffset() - 0.08f * deltaTime);
        }

        // [Z] / [X]: Flip Armrests Up / Down (0 to 90 degrees for lateral wheelchair transfer)
        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        {
            chair->SetArmrestFlipAngle(chair->GetArmrestFlipAngle() + 90.0f * deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        {
            chair->SetArmrestFlipAngle(chair->GetArmrestFlipAngle() - 90.0f * deltaTime);
        }
    }
}


// =====================================================
// FRAMEBUFFER CALLBACK
// =====================================================

void framebuffer_size_callback(
    GLFWwindow*,
    int width,
    int height
)
{
    glViewport(
        0,
        0,
        width,
        height
    );
}


// =====================================================
// MOUSE CALLBACK
// =====================================================

void mouse_callback(
    GLFWwindow*,
    double xpos,
    double ypos
)
{
    if (firstMouse)
    {
        lastX =
            static_cast<float>(xpos);

        lastY =
            static_cast<float>(ypos);

        firstMouse = false;
    }


    float xoffset =
        static_cast<float>(xpos) -
        lastX;


    float yoffset =
        lastY -
        static_cast<float>(ypos);


    lastX =
        static_cast<float>(xpos);

    lastY =
        static_cast<float>(ypos);


    camera.ProcessMouseMovement(
        xoffset,
        yoffset
    );
}