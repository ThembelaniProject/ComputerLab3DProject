
#include "Door.h"

#include "Cube.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Door::Door()
    : openAngle(0.0f),
    targetAngle(0.0f),
    openSpeed(120.0f)
{
}

// ------------------------------------------------------------
// SET DOOR ANGLE
// ------------------------------------------------------------

void Door::SetAngle(float angle)
{
    openAngle = angle;
    targetAngle = angle;
}

// ------------------------------------------------------------
// TOGGLE DOOR
// ------------------------------------------------------------

void Door::Toggle()
{
    if (targetAngle == 0.0f)
    {
        targetAngle = 90.0f;
    }
    else
    {
        targetAngle = 0.0f;
    }
}

// ------------------------------------------------------------
// UPDATE DOOR ANIMATION
// ------------------------------------------------------------

void Door::Update(float deltaTime)
{
    if (openAngle < targetAngle)
    {
        openAngle += openSpeed * deltaTime;

        if (openAngle > targetAngle)
        {
            openAngle = targetAngle;
        }
    }
    else if (openAngle > targetAngle)
    {
        openAngle -= openSpeed * deltaTime;

        if (openAngle < targetAngle)
        {
            openAngle = targetAngle;
        }
    }
}
// ------------------------------------------------------------
// DRAW DOOR
// ------------------------------------------------------------

void Door::Draw(
    Shader& shader,
    const Cube& cube,
    const glm::mat4& parentModel
) const
{
    // ========================================================
    // DOOR ROOT
    // ========================================================

    glm::mat4 root = parentModel;

    root = glm::translate(
        root,
        glm::vec3(
            -7.2f,
            1.0f,
            5.95f
        )
    );

    // ========================================================
    // HINGE PIVOT
    // ========================================================

    root = glm::translate(
        root,
        glm::vec3(
            -0.45f,
            0.0f,
            0.0f
        )
    );

    // ========================================================
    // ROTATE COMPLETE DOOR
    // ========================================================

    root = glm::rotate(
        root,
        glm::radians(openAngle),
        glm::vec3(
            0.0f,
            1.0f,
            0.0f
        )
    );

    // Move back from hinge
    root = glm::translate(
        root,
        glm::vec3(
            0.45f,
            0.0f,
            0.0f
        )
    );

    // ========================================================
    // COLOURS
    // ========================================================

    glm::vec3 frame(
        0.08f,
        0.10f,
        0.12f
    );

    glm::vec3 darkFrame(
        0.04f,
        0.05f,
        0.06f
    );

    glm::vec3 glass(
        0.05f,
        0.30f,
        0.42f
    );

    glm::vec3 glassHighlight(
        0.08f,
        0.45f,
        0.60f
    );

    glm::vec3 silver(
        0.65f,
        0.68f,
        0.70f
    );

    glm::vec3 handle(
        0.20f,
        0.22f,
        0.24f
    );

    glm::vec3 green(
        0.05f,
        0.90f,
        0.25f
    );

    glm::vec3 blue(
        0.05f,
        0.45f,
        0.95f
    );

    glm::vec3 white(
        0.90f,
        0.92f,
        0.94f
    );

    // ========================================================
    // HELPER FUNCTION
    // ========================================================

    auto drawPart =
        [&](const glm::vec3& position,
            const glm::vec3& scale,
            const glm::vec3& color)
        {
            glm::mat4 model = root;

            model = glm::translate(
                model,
                position
            );

            model = glm::scale(
                model,
                scale
            );

            shader.setVec3(
                "objectColor",
                color.x,
                color.y,
                color.z
            );

            shader.setMat4(
                "model",
                model
            );

            cube.Draw();
        };

    // ========================================================
    // MAIN DOOR PANEL
    // ========================================================

    drawPart(
        { 0.0f, 0.0f, 0.0f },
        { 1.20f, 2.00f, 0.10f },
        frame
    );

    // ========================================================
    // OUTER FRAME
    // ========================================================

    // Left
    drawPart(
        { -0.43f, 0.0f, -0.06f },
        { 0.07f, 2.05f, 0.12f },
        darkFrame
    );

    // Right
    drawPart(
        { 0.43f, 0.0f, -0.06f },
        { 0.07f, 2.05f, 0.12f },
        darkFrame
    );

    // Top
    drawPart(
        { 0.0f, 0.98f, -0.06f },
        { 0.90f, 0.07f, 0.12f },
        darkFrame
    );

    // Bottom
    drawPart(
        { 0.0f, -0.98f, -0.06f },
        { 0.90f, 0.07f, 0.12f },
        darkFrame
    );

    // ========================================================
    // SMART GLASS WINDOW
    // ========================================================

    drawPart(
        { 0.0f, 0.28f, -0.075f },
        { 0.62f, 1.20f, 0.025f },
        glass
    );

    // ========================================================
    // GLASS INNER HIGHLIGHT
    // ========================================================

    drawPart(
        { 0.0f, 0.28f, -0.095f },
        { 0.52f, 1.08f, 0.012f },
        glassHighlight
    );

    // ========================================================
    // GLASS FRAME - TOP
    // ========================================================

    drawPart(
        { 0.0f, 0.90f, -0.11f },
        { 0.68f, 0.045f, 0.025f },
        silver
    );

    // ========================================================
    // GLASS FRAME - BOTTOM
    // ========================================================

    drawPart(
        { 0.0f, -0.34f, -0.11f },
        { 0.68f, 0.045f, 0.025f },
        silver
    );

    // ========================================================
    // GLASS FRAME - LEFT
    // ========================================================

    drawPart(
        { -0.34f, 0.28f, -0.11f },
        { 0.045f, 1.25f, 0.025f },
        silver
    );

    // ========================================================
    // GLASS FRAME - RIGHT
    // ========================================================

    drawPart(
        { 0.34f, 0.28f, -0.11f },
        { 0.045f, 1.25f, 0.025f },
        silver
    );

    // ========================================================
    // LOWER DECORATIVE PANEL
    // ========================================================

    drawPart(
        { 0.0f, -0.65f, -0.075f },
        { 0.62f, 0.45f, 0.025f },
        darkFrame
    );

    // Inner lower panel
    drawPart(
        { 0.0f, -0.65f, -0.095f },
        { 0.48f, 0.30f, 0.015f },
        frame
    );

    // ========================================================
    // SMART ACCESS CONTROL
    // ========================================================

    // Access panel
    drawPart(
        { 0.28f, 0.35f, -0.13f },
        { 0.10f, 0.25f, 0.035f },
        darkFrame
    );

    // Screen
    drawPart(
        { 0.28f, 0.40f, -0.16f },
        { 0.065f, 0.10f, 0.015f },
        blue
    );

    // Green access LED
    drawPart(
        { 0.28f, 0.28f, -0.16f },
        { 0.025f, 0.025f, 0.015f },
        green
    );

    // ========================================================
    // SMART DOOR HANDLE
    // ========================================================

    drawPart(
        { 0.34f, -0.05f, -0.15f },
        { 0.045f, 0.30f, 0.045f },
        handle
    );

    // Handle top
    drawPart(
        { 0.34f, 0.12f, -0.16f },
        { 0.09f, 0.045f, 0.055f },
        silver
    );

    // Handle bottom
    drawPart(
        { 0.34f, -0.22f, -0.16f },
        { 0.09f, 0.045f, 0.055f },
        silver
    );

    // ========================================================
    // KICK PLATE
    // ========================================================

    drawPart(
        { 0.0f, -0.86f, -0.13f },
        { 0.68f, 0.10f, 0.035f },
        silver
    );

    // ========================================================
    // DOOR NAME PLATE
    // ========================================================

    drawPart(
        { -0.15f, 0.73f, -0.13f },
        { 0.22f, 0.07f, 0.025f },
        silver
    );

    // ========================================================
    // HINGES
    // ========================================================

    drawPart(
        { -0.45f, 0.65f, 0.0f },
        { 0.08f, 0.16f, 0.12f },
        silver
    );

    drawPart(
        { -0.45f, -0.65f, 0.0f },
        { 0.08f, 0.16f, 0.12f },
        silver
    );
}

