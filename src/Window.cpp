#include "Window.h"

#include "Cube.h"
#include "Shader.h"

#include <glm/gtc/matrix_transform.hpp>


// =====================================================
// CONSTRUCTOR
// =====================================================

Window::Window()
    :
    openAmount(0.0f),
    targetOpenAmount(0.0f),
    animationSpeed(2.5f)
{
}


// =====================================================
// UPDATE ANIMATION
// =====================================================

void Window::Update(
    float deltaTime
)
{
    // -------------------------------------------------
    // OPENING
    // -------------------------------------------------

    if (openAmount < targetOpenAmount)
    {
        openAmount +=
            animationSpeed * deltaTime;


        if (openAmount > targetOpenAmount)
        {
            openAmount =
                targetOpenAmount;
        }
    }


    // -------------------------------------------------
    // CLOSING
    // -------------------------------------------------

    else if (openAmount > targetOpenAmount)
    {
        openAmount -=
            animationSpeed * deltaTime;


        if (openAmount < targetOpenAmount)
        {
            openAmount =
                targetOpenAmount;
        }
    }
}


// =====================================================
// OPEN
// =====================================================

void Window::Open()
{
    targetOpenAmount = 1.0f;
}


// =====================================================
// CLOSE
// =====================================================

void Window::Close()
{
    targetOpenAmount = 0.0f;
}


// =====================================================
// TOGGLE
// =====================================================

void Window::Toggle()
{
    if (targetOpenAmount < 0.5f)
    {
        Open();
    }
    else
    {
        Close();
    }
}


// =====================================================
// DRAW WINDOW
// =====================================================

void Window::Draw(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel
) const
{
    // -------------------------------------------------
    // OUTDOOR VIEW
    // -------------------------------------------------

    DrawOutdoor(
        shader,
        cube,
        parentModel
    );


    // -------------------------------------------------
    // WINDOW FRAME
    // -------------------------------------------------

    DrawFrame(
        shader,
        cube,
        parentModel
    );


    // -------------------------------------------------
    // GLASS
    // -------------------------------------------------

    DrawGlass(
        shader,
        cube,
        parentModel
    );
}


// =====================================================
// OUTDOOR VIEW
// =====================================================

void Window::DrawOutdoor(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel
) const
{
    const float wallX = 7.95f;


    // =================================================
    // SKY
    // =================================================

    glm::mat4 model =
        glm::translate(
            parentModel,
            glm::vec3(
                wallX + 0.12f,
                1.80f,
                0.0f
            )
        );

    model =
        glm::scale(
            model,
            glm::vec3(
                0.04f,
                1.95f,
                6.35f
            )
        );

    shader.setMat4(
        "model",
        model
    );

    shader.setVec3(
        "objectColor",
        0.35f,
        0.70f,
        0.95f
    );

    shader.setFloat(
        "alpha",
        1.0f
    );

    cube.Draw();


    // =================================================
    // GROUND
    // =================================================

    model =
        glm::translate(
            parentModel,
            glm::vec3(
                wallX + 0.10f,
                0.92f,
                0.0f
            )
        );

    model =
        glm::scale(
            model,
            glm::vec3(
                0.03f,
                0.28f,
                6.30f
            )
        );

    shader.setMat4(
        "model",
        model
    );

    shader.setVec3(
        "objectColor",
        0.20f,
        0.50f,
        0.20f
    );

    cube.Draw();


    // =================================================
    // BUILDING 1
    // =================================================

    model =
        glm::translate(
            parentModel,
            glm::vec3(
                wallX + 0.06f,
                1.65f,
                -2.60f
            )
        );

    model =
        glm::scale(
            model,
            glm::vec3(
                0.03f,
                1.00f,
                1.15f
            )
        );

    shader.setMat4(
        "model",
        model
    );

    shader.setVec3(
        "objectColor",
        0.48f,
        0.48f,
        0.50f
    );

    cube.Draw();


    // =================================================
    // BUILDING 2
    // =================================================

    model =
        glm::translate(
            parentModel,
            glm::vec3(
                wallX + 0.05f,
                1.45f,
                2.25f
            )
        );

    model =
        glm::scale(
            model,
            glm::vec3(
                0.03f,
                0.80f,
                1.25f
            )
        );

    shader.setMat4(
        "model",
        model
    );

    shader.setVec3(
        "objectColor",
        0.45f,
        0.30f,
        0.20f
    );

    cube.Draw();


    // =================================================
    // BUILDING WINDOWS
    // =================================================

    const float windowZ[] =
    {
        -2.85f,
        -2.45f,
        -2.05f
    };


    for (float z : windowZ)
    {
        model =
            glm::translate(
                parentModel,
                glm::vec3(
                    wallX + 0.025f,
                    1.75f,
                    z
                )
            );

        model =
            glm::scale(
                model,
                glm::vec3(
                    0.02f,
                    0.18f,
                    0.18f
                )
            );

        shader.setMat4(
            "model",
            model
        );

        shader.setVec3(
            "objectColor",
            0.55f,
            0.80f,
            0.95f
        );

        cube.Draw();
    }


    // =================================================
    // TREE 1 - TRUNK
    // =================================================

    model =
        glm::translate(
            parentModel,
            glm::vec3(
                wallX + 0.02f,
                1.55f,
                1.00f
            )
        );

    model =
        glm::scale(
            model,
            glm::vec3(
                0.06f,
                0.75f,
                0.10f
            )
        );

    shader.setMat4(
        "model",
        model
    );

    shader.setVec3(
        "objectColor",
        0.35f,
        0.20f,
        0.08f
    );

    cube.Draw();


    // =================================================
    // TREE 1 - LEAVES
    // =================================================

    model =
        glm::translate(
            parentModel,
            glm::vec3(
                wallX + 0.02f,
                2.10f,
                1.00f
            )
        );

    model =
        glm::scale(
            model,
            glm::vec3(
                0.12f,
                0.45f,
                0.55f
            )
        );

    shader.setMat4(
        "model",
        model
    );

    shader.setVec3(
        "objectColor",
        0.15f,
        0.55f,
        0.18f
    );

    cube.Draw();


    // =================================================
    // TREE 2 - TRUNK
    // =================================================

    model =
        glm::translate(
            parentModel,
            glm::vec3(
                wallX + 0.02f,
                1.45f,
                -0.50f
            )
        );

    model =
        glm::scale(
            model,
            glm::vec3(
                0.06f,
                0.65f,
                0.08f
            )
        );

    shader.setMat4(
        "model",
        model
    );

    shader.setVec3(
        "objectColor",
        0.35f,
        0.20f,
        0.08f
    );

    cube.Draw();


    // =================================================
    // TREE 2 - LEAVES
    // =================================================

    model =
        glm::translate(
            parentModel,
            glm::vec3(
                wallX + 0.02f,
                2.00f,
                -0.50f
            )
        );

    model =
        glm::scale(
            model,
            glm::vec3(
                0.12f,
                0.40f,
                0.50f
            )
        );

    shader.setMat4(
        "model",
        model
    );

    shader.setVec3(
        "objectColor",
        0.12f,
        0.50f,
        0.16f
    );

    cube.Draw();
}


// =====================================================
// WINDOW FRAME
// =====================================================

void Window::DrawFrame(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel
) const
{
    const float wallX = 7.95f;


    // Window frame colour

    const glm::vec3 frameColor(
        0.82f,
        0.82f,
        0.82f
    );


    glm::mat4 model;


    // =================================================
    // LEFT OUTER FRAME
    // =================================================

    model =
        glm::translate(
            parentModel,
            glm::vec3(
                wallX,
                1.80f,
                -3.25f
            )
        );

    model =
        glm::scale(
            model,
            glm::vec3(
                0.08f,
                2.10f,
                0.08f
            )
        );

    shader.setMat4(
        "model",
        model
    );

    shader.setVec3(
        "objectColor",
        frameColor
    );

    shader.setFloat(
        "alpha",
        1.0f
    );

    cube.Draw();


    // =================================================
    // RIGHT OUTER FRAME
    // =================================================

    model =
        glm::translate(
            parentModel,
            glm::vec3(
                wallX,
                1.80f,
                3.25f
            )
        );

    model =
        glm::scale(
            model,
            glm::vec3(
                0.08f,
                2.10f,
                0.08f
            )
        );

    shader.setMat4(
        "model",
        model
    );

    shader.setVec3(
        "objectColor",
        frameColor
    );

    cube.Draw();


    // =================================================
    // TOP FRAME
    // =================================================

    model =
        glm::translate(
            parentModel,
            glm::vec3(
                wallX,
                2.82f,
                0.0f
            )
        );

    model =
        glm::scale(
            model,
            glm::vec3(
                0.08f,
                0.08f,
                6.60f
            )
        );

    shader.setMat4(
        "model",
        model
    );

    shader.setVec3(
        "objectColor",
        frameColor
    );

    cube.Draw();


    // =================================================
    // BOTTOM FRAME
    // =================================================

    model =
        glm::translate(
            parentModel,
            glm::vec3(
                wallX,
                0.78f,
                0.0f
            )
        );

    model =
        glm::scale(
            model,
            glm::vec3(
                0.08f,
                0.08f,
                6.60f
            )
        );

    shader.setMat4(
        "model",
        model
    );

    shader.setVec3(
        "objectColor",
        frameColor
    );

    cube.Draw();


    // =================================================
    // CENTER VERTICAL FRAME
    // =================================================

    model =
        glm::translate(
            parentModel,
            glm::vec3(
                wallX - 0.01f,
                1.80f,
                0.0f
            )
        );

    model =
        glm::scale(
            model,
            glm::vec3(
                0.09f,
                1.98f,
                0.08f
            )
        );

    shader.setMat4(
        "model",
        model
    );

    shader.setVec3(
        "objectColor",
        frameColor
    );

    cube.Draw();


    // =================================================
    // HORIZONTAL DIVIDER
    // =================================================

    model =
        glm::translate(
            parentModel,
            glm::vec3(
                wallX - 0.01f,
                1.80f,
                0.0f
            )
        );

    model =
        glm::scale(
            model,
            glm::vec3(
                0.09f,
                0.05f,
                6.35f
            )
        );

    shader.setMat4(
        "model",
        model
    );

    shader.setVec3(
        "objectColor",
        frameColor
    );

    cube.Draw();


    // =================================================
    // HANDLE
    // =================================================

    model =
        glm::translate(
            parentModel,
            glm::vec3(
                wallX - 0.10f,
                1.65f,
                0.35f
            )
        );

    model =
        glm::scale(
            model,
            glm::vec3(
                0.06f,
                0.30f,
                0.06f
            )
        );

    shader.setMat4(
        "model",
        model
    );

    shader.setVec3(
        "objectColor",
        0.12f,
        0.12f,
        0.12f
    );

    cube.Draw();
}


// =====================================================
// GLASS
// =====================================================

void Window::DrawGlass(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel
) const
{
    // Put glass slightly behind the frame.

    const float wallX = 7.98f;


    // -------------------------------------------------
    // Transparency
    // -------------------------------------------------

    shader.setFloat(
        "alpha",
        0.30f
    );


    // -------------------------------------------------
    // How far the glass slides open
    // -------------------------------------------------

    const float slideDistance = 2.0f;


    float slide =
        slideDistance *
        openAmount;


    // =================================================
    // LEFT GLASS PANEL
    // =================================================

    glm::mat4 model =
        glm::translate(
            parentModel,
            glm::vec3(
                wallX,
                1.80f,
                -1.58f - slide
            )
        );

    model =
        glm::scale(
            model,
            glm::vec3(
                0.025f,
                1.90f,
                3.10f
            )
        );

    shader.setMat4(
        "model",
        model
    );

    shader.setVec3(
        "objectColor",
        0.55f,
        0.80f,
        0.95f
    );

    cube.Draw();


    // =================================================
    // RIGHT GLASS PANEL
    // =================================================

    model =
        glm::translate(
            parentModel,
            glm::vec3(
                wallX,
                1.80f,
                1.58f + slide
            )
        );

    model =
        glm::scale(
            model,
            glm::vec3(
                0.025f,
                1.90f,
                3.10f
            )
        );

    shader.setMat4(
        "model",
        model
    );

    shader.setVec3(
        "objectColor",
        0.55f,
        0.80f,
        0.95f
    );

    cube.Draw();


    // -------------------------------------------------
    // RESET ALPHA
    // -------------------------------------------------

    shader.setFloat(
        "alpha",
        1.0f
    );
}